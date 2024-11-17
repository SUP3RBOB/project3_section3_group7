#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

using namespace Qt;

const float TICK_RATE = 0.016f;
const float TIMER_RATE = 16.f;
const float SIMULATION_SPEED = 500.f;
const int TRAIL_LENGTH = 1000;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Window setup
    setWindowTitle("Reach Spaceship Controller");
    setFixedSize(1280, 720);

    // Creating objects
    simulation = new Simulation();
    connect(&simulation->GetSpaceship().GetPower(), &Power::OnPowerActivated, this, &MainWindow::OnPower);

    updateTimer = new QTimer();
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::Update);
    updateTimer->start(TIMER_RATE);

    // Paint view setup
    currentScale = 5e-5f;
    currentScale /= 4.25f;
    pan = QVector2D();

    const float PAN_YOFFSET = 13000000.f;
    pan.setY(pan.y() + PAN_YOFFSET);

    spaceshipTrail = QList<QVector2D>();
    spaceshipTrail.append(simulation->GetSpaceship().GetNavigation().Position);

    // Initialize indicator sprites
    onSprite = QPixmap(":/Images/Images/green light.png");
    offSprite = QPixmap(":/Images/Images/red light.png");

    // Startup
    Startup();
}

MainWindow::~MainWindow() {
    delete updateTimer;
    delete simulation;
    delete ui;
}

bool MainWindow::IsPowerOn() {
    return simulation->GetSpaceship().GetPower().IsOn();
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

    power.SetOn(power.IsOn());
    ui->Hull->display(qRound(hull.GetIntegrity()));

    ui->TempSlider->setValue(qRound(ls.GetTemp()));
    ui->OxygenSlider->setValue(qRound(ls.GetOxygen()));

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
    Power& power = simulation->GetSpaceship().GetPower();
    Lights& lights = simulation->GetSpaceship().GetLights();

    ui->TempSlider->setEnabled(on);
    ui->OxygenSlider->setEnabled(on);
    ui->LightsButton->setEnabled(on);
    ui->ShipMessagesToggleButton->setEnabled(on);
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
    ui->PowerIndicator->setPixmap(power.IsOn() ? onSprite : offSprite);

    power.Save("power.txt");
}

