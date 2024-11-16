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

    Ui::MainWindow *ui;

    Simulation* simulation;
    QTimer* updateTimer;

    void Update();

    float currentScale;
    QVector2D pan;
    QList<QVector2D> spaceshipTrail;

    QPixmap onSprite;
    QPixmap offSprite;

    QPoint ToScreenCoordinates(const QVector2D& position);

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_TempSlider_valueChanged(int value);
    void on_OxygenSlider_valueChanged(int value);
    void OnPower(bool on);
};
#endif // MAINWINDOW_H
