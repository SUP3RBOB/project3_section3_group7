#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spaceship.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Spaceship ship = Spaceship();
}

MainWindow::~MainWindow()
{
    delete ui;
}
