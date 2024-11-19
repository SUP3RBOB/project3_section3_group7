#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulation.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow* ui;  // UI elements
    Simulation* simulation;  // Handles spaceship and Earth interaction

    QTimer* updateTimer;
    QTimer* commsTimer;
    QTimer* navTimer;
    QTimer* hullTimer;

    float currentScale;  // Scale for orbit view
    QVector2D pan;  // Pan offset
    QList<QVector2D> spaceshipTrail;  // Trail of spaceship's positions

    QPixmap onSprite;  // Indicator for "on" state
    QPixmap offSprite;  // Indicator for "off" state

    void Startup();  // Initialize modules and connect them to UI
    void Update();  // Periodic update

    QPoint ToScreenCoordinates(const QVector2D& position);  // Convert world to screen coordinates
    bool IsPowerOn();  // Check if spaceship power is on

protected:
    void paintEvent(QPaintEvent *event) override;  // Custom rendering

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_TempSlider_valueChanged(int value);
    void on_OxygenSlider_valueChanged(int value);
    void OnPower(bool on);
    void on_LightsButton_clicked();
    void on_PowerButton_clicked();
    void ReceiveRandomMessage();
    void RandomMessageReceived(QString message);
    void on_ShipMessagesToggleButton_clicked();
    void on_ThrustUpButton_clicked();
    void on_ThrustRightButton_clicked();
    void on_ThrustDownButton_clicked();
    void on_ThrustLeftButton_clicked();
    void on_ThrustClearButton_clicked();
    void UpdateHull();
    void SaveNavigation();
};

#endif // MAINWINDOW_H
