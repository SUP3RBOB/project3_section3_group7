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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;

    Simulation* simulation;
    QTimer* updateTimer;

    void Update();

    float currentScale;
    QVector2D pan;

    QPoint ToScreenCoordinates(const QVector2D& position);
};
#endif // MAINWINDOW_H
