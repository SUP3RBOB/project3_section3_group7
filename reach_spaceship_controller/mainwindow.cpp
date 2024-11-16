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
}

MainWindow::~MainWindow() {
    delete updateTimer;
    delete simulation;
    delete ui;
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
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(shipPoint, 5, 5);
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

