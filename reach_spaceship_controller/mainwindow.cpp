#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

const float TICK_RATE = 0.016f;
const float TIMER_RATE = 16.f;
const float SIMULATION_SPEED = 500.f;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    simulation = new Simulation();

    updateTimer = new QTimer();
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::Update);
    updateTimer->start(TIMER_RATE);

    currentScale = 5e-5f;
    currentScale /= 1.5;
    pan = QVector2D();

    //simulation->GetSpaceship().GetNavigation().ThrusterX().SetThrust(1.f);
    float shipMass = simulation->GetSpaceship().GetMass();
    simulation->GetSpaceship().GetNavigation().ApplyThrust(shipMass, TICK_RATE);
}

MainWindow::~MainWindow() {
    delete updateTimer;
    delete simulation;
    delete ui;
}

QPoint MainWindow::ToScreenCoordinates(const QVector2D& position) {
    QVector2D earthPosition = simulation->GetEarth().GetPosition();
    float offsetX = -earthPosition.x() + pan.x();
    float offsetY = -earthPosition.y() + pan.y();

    int x = static_cast<int>(width() / 2 + (position.x() + offsetX) * currentScale);
    int y = static_cast<int>(height() / 2 - (position.y() + offsetY) * currentScale);
    return QPoint(x, y);
}

void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter painter = QPainter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::black);

    Navigation& nav = simulation->GetSpaceship().GetNavigation();
    Earth& earth = simulation->GetEarth();

    // Draw earth
    QPoint earthPoint = ToScreenCoordinates(earth.GetPosition());
    int earthRadius = static_cast<int>(earth.GetRadius() * currentScale);
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(earthPoint, earthRadius, earthRadius);

    // Draw spaceship
    QPoint shipPoint = ToScreenCoordinates(nav.Position);
    painter.setBrush(Qt::yellow);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(shipPoint, 5, 5);
}

void MainWindow::Update() {
    simulation->Update(TICK_RATE, SIMULATION_SPEED);
    repaint();
}

