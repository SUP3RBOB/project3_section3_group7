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
private:
    Q_OBJECT

    Ui::MainWindow* ui;

    Simulation* simulation;

    QTimer* updateTimer;
    QTimer* commsTimer;
    QTimer* navTimer;
    QTimer* hullTimer;

    void Startup();
    void Update();

    float currentScale;
    QVector2D pan;
    QList<QVector2D> spaceshipTrail;

    QPixmap onSprite;
    QPixmap offSprite;

    QPoint ToScreenCoordinates(const QVector2D& position);
    bool IsPowerOn();
    void UpdateMap();

protected:
    void paintEvent(QPaintEvent *event) override;

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
