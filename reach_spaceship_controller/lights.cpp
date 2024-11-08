#include "lights.h"
#include <QFile>
#include <QTextStream>
#include <QVariant>

Lights::Lights() {
    this->turnedOn = false;
}

void Lights::turnOff(){
    turnedOn = false;
}
void Lights::turnOn(){
    turnedOn = true;
}
bool Lights::isOn(){
    return(turnedOn);
}

void Lights::Save(QString fileName) {
    QFile file = QFile(fileName);
    file.open(QIODevice::WriteOnly);

    QTextStream stream = QTextStream(&file);
    stream << turnedOn << Qt::endl;

    file.close();
}

void Lights::Load(QString fileName) {
    QFile file = QFile(fileName);
    bool success = file.open(QIODevice::ReadOnly);

    if (!success) {
        return;
    }

    QTextStream stream = QTextStream(&file);
    QString value = stream.readLine();
    turnedOn = QVariant(value).toBool();

    file.close();
}


