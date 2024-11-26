#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QKeyEvent>
#include <QFile>
#include <QApplication>
#include <QProcess>

using namespace Qt;

const float TICK_RATE = 0.016f;
const float SIMULATION_SPEED = 500.f;
const int TRAIL_LENGTH = 1000;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Reshuffle seed
    srand(time(NULL));

    // Window setup
    setWindowTitle("Reach Spaceship Controller");
    setFixedSize(1280, 720);

    // Creating objects
    simulation = new Simulation();
    connect(&simulation->GetSpaceship().GetPower(), &Power::OnPowerActivated, this, &MainWindow::OnPower);

    updateTimer = new QTimer();
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::Update);
    const float UPDATE_TIMER_RATE = 16.f;
    updateTimer->start(UPDATE_TIMER_RATE);

    commsTimer = new QTimer();
    connect(commsTimer, &QTimer::timeout, this, &MainWindow::ReceiveRandomMessage);
    connect(&simulation->GetSpaceship().GetComms(), &Communication::OnMessageReceived, this, &MainWindow::RandomMessageReceived);
    const float TIME_TO_RECEIVE_MESSAGE = 15000.f;
    commsTimer->start(TIME_TO_RECEIVE_MESSAGE);

    hullTimer = new QTimer();
    connect(hullTimer, &QTimer::timeout, this, &MainWindow::UpdateHull);
    const float HULL_TIME = 9000.f;
    hullTimer->start(HULL_TIME);

    navTimer = new QTimer();
    connect(navTimer, &QTimer::timeout, this, &MainWindow::SaveNavigation);
    connect(navTimer, &QTimer::timeout, this, &MainWindow::UpdateMap);
    const float NAV_SAVE_TIME = 1000.f;
    navTimer->start(NAV_SAVE_TIME);

    // Paint view setup
    currentScale = 5e-5f;
    currentScale /= 4.25f;
    pan = QVector2D();

    const float PAN_YOFFSET = 13000000.f;
    pan.setY(pan.y() + PAN_YOFFSET);

    spaceshipTrail = QList<QVector2D>();

    // Initialize indicator sprites
    onSprite = QPixmap(":/Images/Images/green light.png");
    offSprite = QPixmap(":/Images/Images/red light.png");

    // Startup
    Startup();
}

MainWindow::~MainWindow() {
    delete navTimer;
    delete hullTimer;
    delete commsTimer;
    delete updateTimer;
    delete simulation;
    delete ui;
}

bool MainWindow::IsPowerOn() {
    return simulation->GetSpaceship().GetPower().IsOn();
}

void MainWindow::UpdateMap() {
    if (!IsPowerOn()) {
        return;
    }

    Map& map = simulation->GetSpaceship().GetMap();
    Navigation& nav = simulation->GetSpaceship().GetNavigation();

    QTreeWidgetItem* item = ui->PlanetTable->topLevelItem(0);
    item->setText(0, simulation->GetEarth().GetName());

    QString distance = QString::number(nav.Position.distanceToPoint(simulation->GetEarth().GetPosition()) / 200000000.f) + " AU";
    item->setText(1, distance);

    for (int i = 0; i < map.list.count(); i++) {
        Planet& planet = map.list[i];
        QTreeWidgetItem* item = ui->PlanetTable->topLevelItem(i+1);
        item->setText(0, planet.GetName());

        QString distance = QString::number((nav.Position.distanceToPoint(planet.GetPosition())) / 150000000.f) + " AU";
        item->setText(1, distance);
    }
}

// Apply object coordinates with the pan and scale
QPoint MainWindow::ToScreenCoordinates(const QVector2D& position) {
    QVector2D earthPosition = simulation->GetEarth().GetPosition();
    float offsetX = -earthPosition.x() + pan.x();
    float offsetY = -earthPosition.y() + pan.y();

    int x = static_cast<int>(width() / 2 + (position.x() + offsetX) * currentScale);
    int y = static_cast<int>(height() / 2 - (position.y() + offsetY) * currentScale);
    return QPoint(x, y);
}

// For resetting all saves and restarting the application
void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Key_Backspace) {
        DeleteModuleSaves();
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
}

// Draw orbit view
void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter painter = QPainter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), black);

    // Don't draw orbit if there's no power
    if (!IsPowerOn()) {
        return;
    }

    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    Earth& earth = simulation->GetEarth();

    // Draw earth
    QPoint earthPoint = ToScreenCoordinates(earth.GetPosition());
    int earthRadius = static_cast<int>(earth.GetRadius() * currentScale);
    painter.setBrush(blue);
    painter.setPen(NoPen);
    painter.drawEllipse(earthPoint, earthRadius, earthRadius);

    // Draw spaceship trail
    painter.setBrush(NoBrush);
    painter.setPen(gray);
    for (int i = 1; i < spaceshipTrail.count(); i++) {
        QPoint start = ToScreenCoordinates(spaceshipTrail[i - 1]);
        QPoint end = ToScreenCoordinates(spaceshipTrail[i]);
        painter.drawLine(start, end);
    }

    // Draw spaceship
    QPoint shipPoint = ToScreenCoordinates(nav.Position);
    painter.setBrush(yellow);
    painter.setPen(NoPen);
    painter.drawEllipse(shipPoint, 5, 5);
}

// Startup for modules and UI integration
void MainWindow::Startup() {
    simulation->GetSpaceship().Load();
    simulation->GetSpaceship().Save();

    Power& power = simulation->GetSpaceship().GetPower();
    Hull& hull = simulation->GetSpaceship().GetHull();
    LifeSupport& ls = simulation->GetSpaceship().GetLifeSupport();
    Lights& lights = simulation->GetSpaceship().GetLights();
    Communication& comms = simulation->GetSpaceship().GetComms();

    // Power
    power.SetOn(power.IsOn());
    ui->Hull->display(qRound(hull.GetIntegrity()));

    // Life support
    ui->TempSlider->setValue(qRound(ls.GetTemp()));
    ui->OxygenSlider->setValue(qRound(ls.GetOxygen()));

    // Lights
    ui->LightsOverlay->setAttribute(WA_TransparentForMouseEvents);

    bool lightsAreOn = power.IsOn() && lights.isOn();
    ui->LightsOverlay->setVisible(!lightsAreOn);
    ui->LightsIndicator->setPixmap(lightsAreOn ? onSprite : offSprite);

    // Map planet table UI
    Map& map = simulation->GetSpaceship().GetMap();
    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, simulation->GetEarth().GetName());

    QString distance = QString::number(nav.Position.distanceToPoint(simulation->GetEarth().GetPosition()) / 200000000.f) + " AU";
    item->setText(1, distance);
    ui->PlanetTable->addTopLevelItem(item);

    for (Planet& planet : map.list) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, planet.GetName());

        QString distance = QString::number((nav.Position.distanceToPoint(planet.GetPosition())) / 150000000.f) + " AU";
        item->setText(1, distance);
        ui->PlanetTable->addTopLevelItem(item);
    }

    // Comms
    ui->ShipMessagesToggleButton->setText(comms.CanReceiveMessages() ? "Enabled" : "Disabled");
    QString style = "color: rgb(0, 0, 0); border-radius: 10px; ";
    style += comms.CanReceiveMessages() ? "background-color: rgb(0, 170, 0);" : "background-color: rgb(170, 0, 0);";
    ui->ShipMessagesToggleButton->setStyleSheet(style);
    if (comms.MessagesReceived.count() > 0) {
        for (QString& message : comms.MessagesReceived) {
            ui->MessagesList->addItem(message);
        }
    }

    // Navigation and Thrusters
    ui->ThrusterXLabel->display(nav.ThrusterX().GetThrust());
    ui->ThrusterYLabel->display(nav.ThrusterY().GetThrust());
    spaceshipTrail.append(simulation->GetSpaceship().GetNavigation().Position);

    // Hull
    ui->Hull->display(qRound(hull.GetIntegrity()));
}

// Update every 'frame'
void MainWindow::Update() {
    simulation->Update(TICK_RATE, SIMULATION_SPEED);

    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    spaceshipTrail.append(nav.Position);
    if (spaceshipTrail.count() > TRAIL_LENGTH) {
        spaceshipTrail.removeFirst();
    }

    repaint();
}

void MainWindow::OnPower(bool on) {
    Lights& lights = simulation->GetSpaceship().GetLights();

    if (!on) {
        on_ThrustClearButton_clicked();
    }

    ui->PowerIndicator->setPixmap(on ? onSprite : offSprite);
    ui->TempSlider->setEnabled(on);
    ui->OxygenSlider->setEnabled(on);
    ui->LightsButton->setEnabled(on);
    ui->ShipMessagesToggleButton->setEnabled(on);
    ui->ThrustDownButton->setEnabled(on);
    ui->ThrustUpButton->setEnabled(on);
    ui->ThrustLeftButton->setEnabled(on);
    ui->ThrustRightButton->setEnabled(on);
    ui->ThrustClearButton->setEnabled(on);
    ui->LightsButton->setEnabled(on);
    ui->LightsOverlay->setVisible(!(on && lights.isOn()));
}

void MainWindow::on_TempSlider_valueChanged(int value) {
    LifeSupport& ls = simulation->GetSpaceship().GetLifeSupport();

    ls.SetTemp(value);
    ui->TempLabel->display(qRound(ls.GetTemp()));

    ls.Save("lifesupport.txt");
}


void MainWindow::on_OxygenSlider_valueChanged(int value) {
    LifeSupport& ls = simulation->GetSpaceship().GetLifeSupport();

    ls.SetOxygen(value);
    ui->OxygenLabel->display(qRound(ls.GetOxygen()));

    ls.Save("lifesupport.txt");
}


void MainWindow::on_LightsButton_clicked() {
    Lights& lights = simulation->GetSpaceship().GetLights();

    if (lights.isOn()) {
        lights.turnOff();
        ui->LightsIndicator->setPixmap(offSprite);
        ui->LightsOverlay->setVisible(true);
    } else {
        lights.turnOn();
        ui->LightsIndicator->setPixmap(onSprite);
        ui->LightsOverlay->setVisible(false);
    }

    lights.Save("lights.txt");
}


void MainWindow::on_PowerButton_clicked() {
    Power& power = simulation->GetSpaceship().GetPower();

    power.SetOn(!power.IsOn());

    power.Save("power.txt");
}

void MainWindow::ReceiveRandomMessage() {
    Communication& comms = simulation->GetSpaceship().GetComms();
    if (comms.CanReceiveMessages()) {
        comms.ReceiveRandomMessage();
        comms.Save("comms.txt");
    }
}

void MainWindow::RandomMessageReceived(QString message) {
    ui->MessagesList->addItem(message);
}


void MainWindow::on_ShipMessagesToggleButton_clicked() {
    Communication& comms = simulation->GetSpaceship().GetComms();
    comms.ToggleReceiveMessages();
    ui->ShipMessagesToggleButton->setText(comms.CanReceiveMessages() ? "Enabled" : "Disabled");
    QString style = "color: rgb(0, 0, 0); border-radius: 10px; ";
    style += comms.CanReceiveMessages() ? "background-color: rgb(0, 170, 0);" : "background-color: rgb(170, 0, 0);";
    ui->ShipMessagesToggleButton->setStyleSheet(style);
    comms.Save("comms.txt");
}


void MainWindow::on_ThrustUpButton_clicked() {
    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    nav.ThrusterY().SetThrust(1.f);
    nav.ApplyThrust(simulation->GetSpaceship().GetMass(), TICK_RATE);
    ui->ThrusterYLabel->display(nav.ThrusterY().GetThrust());
    nav.Save("navigation.txt");
}


void MainWindow::on_ThrustRightButton_clicked() {
    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    nav.ThrusterX().SetThrust(1.f);
    nav.ApplyThrust(simulation->GetSpaceship().GetMass(), TICK_RATE);
    ui->ThrusterXLabel->display(nav.ThrusterX().GetThrust());
    nav.Save("navigation.txt");
}


void MainWindow::on_ThrustDownButton_clicked() {
    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    nav.ThrusterY().SetThrust(-1.f);
    nav.ApplyThrust(simulation->GetSpaceship().GetMass(), TICK_RATE);
    ui->ThrusterYLabel->display(nav.ThrusterY().GetThrust());
    nav.Save("navigation.txt");
}


void MainWindow::on_ThrustLeftButton_clicked() {
    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    nav.ThrusterX().SetThrust(-1.f);
    nav.ApplyThrust(simulation->GetSpaceship().GetMass(), TICK_RATE);
    ui->ThrusterXLabel->display(nav.ThrusterX().GetThrust());
    nav.Save("navigation.txt");
}


void MainWindow::on_ThrustClearButton_clicked() {
    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    nav.ThrusterY().SetThrust(0.f);
    nav.ThrusterX().SetThrust(0.f);
    nav.ApplyThrust(simulation->GetSpaceship().GetMass(), TICK_RATE);
    ui->ThrusterXLabel->display(nav.ThrusterX().GetThrust());
    ui->ThrusterYLabel->display(nav.ThrusterY().GetThrust());
    nav.Save("navigation.txt");
}

void MainWindow::UpdateHull() {
    Hull& hull = simulation->GetSpaceship().GetHull();

    if (hull.GetIntegrity() - 1.f <= 0) {
        hull.SetIntegrity(hull.GetIntegrity() + 1);
    } else {
        int randomNumber = rand() % 2;
        int num = randomNumber == 1 ? 1 : -1;
        hull.SetIntegrity(hull.GetIntegrity() + num);
    }

    ui->Hull->display(qRound(hull.GetIntegrity()));
    hull.Save("hull.txt");
}

void MainWindow::SaveNavigation() {
    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    nav.Save("navigation.txt");
}

void MainWindow::DeleteModuleSaves() {
    if (QFile::exists("navigation.txt")) {
        QFile::remove("navigation.txt");
    }

    if (QFile::exists("power.txt")) {
        QFile::remove("power.txt");
    }

    if (QFile::exists("lights.txt")) {
        QFile::remove("lights.txt");
    }

    if (QFile::exists("comms.txt")) {
        QFile::remove("comms.txt");
    }

    if (QFile::exists("lifesupport.txt")) {
        QFile::remove("lifesupport.txt");
    }

    if (QFile::exists("thruster_x.txt")) {
        QFile::remove("thruster_x.txt");
    }

    if (QFile::exists("thruster_y.txt")) {
        QFile::remove("thruster_y.txt");
    }
}
