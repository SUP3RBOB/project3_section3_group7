#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

const float TICK_RATE = 0.016f;  // Simulation interval
const float SIMULATION_SPEED = 500.f;  // Speed multiplier
const int TRAIL_LENGTH = 1000;  // Max trail length

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("Reach Spaceship Controller");
    setFixedSize(1280, 720);

    simulation = new Simulation();

    // Connect module signals to update UI
    connect(&simulation->GetSpaceship().GetPower(), &Power::OnPowerActivated, this, &MainWindow::OnPower);
    connect(&simulation->GetSpaceship().GetComms(), &Communication::OnMessageReceived, this, &MainWindow::RandomMessageReceived);

    // Timers for periodic updates
    updateTimer = new QTimer();
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::Update);
    updateTimer->start(16);

    commsTimer = new QTimer();
    connect(commsTimer, &QTimer::timeout, this, &MainWindow::ReceiveRandomMessage);
    commsTimer->start(15000);

    hullTimer = new QTimer();
    connect(hullTimer, &QTimer::timeout, this, &MainWindow::UpdateHull);
    hullTimer->start(9000);

    navTimer = new QTimer();
    connect(navTimer, &QTimer::timeout, this, &MainWindow::SaveNavigation);
    navTimer->start(1000);

    // Initialize scale and offset for rendering
    currentScale = 5e-5f / 4.25f;
    pan = QVector2D(0, 13000000.0f);

    onSprite = QPixmap(":/Images/Images/green light.png");
    offSprite = QPixmap(":/Images/Images/red light.png");

    Startup();
}

MainWindow::~MainWindow() {
    delete updateTimer;
    delete commsTimer;
    delete hullTimer;
    delete navTimer;
    delete simulation;
    delete ui;
}

void MainWindow::Startup() {
    simulation->GetSpaceship().Load();  // Load spaceship state

    Power& power = simulation->GetSpaceship().GetPower();
    Hull& hull = simulation->GetSpaceship().GetHull();
    LifeSupport& ls = simulation->GetSpaceship().GetLifeSupport();
    Lights& lights = simulation->GetSpaceship().GetLights();
    Communication& comms = simulation->GetSpaceship().GetComms();

    // Update UI with module states
    power.SetOn(power.IsOn());
    ui->Hull->display(qRound(hull.GetIntegrity()));
    ui->TempSlider->setValue(qRound(ls.GetTemp()));
    ui->OxygenSlider->setValue(qRound(ls.GetOxygen()));

    bool lightsAreOn = power.IsOn() && lights.isOn();
    ui->LightsOverlay->setVisible(!lightsAreOn);
    ui->LightsIndicator->setPixmap(lightsAreOn ? onSprite : offSprite);

    // Populate planet data
    Map& map = simulation->GetSpaceship().GetMap();
    Navigation& nav = simulation->GetSpaceship().GetNavigation();

    QTreeWidgetItem* earthItem = new QTreeWidgetItem();
    earthItem->setText(0, simulation->GetEarth().GetName());
    earthItem->setText(1, QString::number(nav.Position.distanceToPoint(simulation->GetEarth().GetPosition()) / 200000000.f) + " AU");
    ui->PlanetTable->addTopLevelItem(earthItem);

    for (Planet& planet : map.list) {
        QTreeWidgetItem* planetItem = new QTreeWidgetItem();
        planetItem->setText(0, planet.GetName());
        planetItem->setText(1, QString::number((nav.Position.distanceToPoint(planet.GetPosition())) / 150000000.f) + " AU");
        ui->PlanetTable->addTopLevelItem(planetItem);
    }

    ui->ShipMessagesToggleButton->setText(comms.CanReceiveMessages() ? "Enabled" : "Disabled");

    // Add received messages
    for (QString& message : comms.MessagesReceived) {
        ui->MessagesList->addItem(message);
    }

    ui->ThrusterXLabel->display(nav.ThrusterX().GetThrust());
    ui->ThrusterYLabel->display(nav.ThrusterY().GetThrust());

    spaceshipTrail.append(nav.Position);
}

void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::black);

    if (!IsPowerOn()) return;

    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    Earth& earth = simulation->GetEarth();

    // Draw Earth
    QPoint earthPoint = ToScreenCoordinates(earth.GetPosition());
    painter.setBrush(Qt::blue);
    painter.drawEllipse(earthPoint, static_cast<int>(earth.GetRadius() * currentScale), static_cast<int>(earth.GetRadius() * currentScale));

    // Draw spaceship trail
    painter.setPen(Qt::gray);
    for (int i = 1; i < spaceshipTrail.count(); i++) {
        painter.drawLine(ToScreenCoordinates(spaceshipTrail[i - 1]), ToScreenCoordinates(spaceshipTrail[i]));
    }

    // Draw spaceship
    QPoint shipPoint = ToScreenCoordinates(nav.Position);
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(shipPoint, 5, 5);
}

void MainWindow::Update() {
    simulation->Update(TICK_RATE, SIMULATION_SPEED);

    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    spaceshipTrail.append(nav.Position);
    if (spaceshipTrail.count() > TRAIL_LENGTH) spaceshipTrail.removeFirst();

    repaint();
}
