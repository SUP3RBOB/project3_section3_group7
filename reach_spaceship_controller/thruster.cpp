#include "thruster.h"
#include <QFile>
#include <QTextStream>

using namespace Qt;

Thruster::Thruster() {
    thrust = 0.f;
}

float Thruster::GetThrust() const {
    return thrust;
}

void Thruster::SetThrust(float thrust) {
    this->thrust = thrust;
}

void Thruster::Save(QString fileName) {
    QFile file = QFile(fileName);
    bool success = file.open(QIODevice::WriteOnly);

    if (!success) {
        return;
    }

    QTextStream stream = QTextStream(&file);
    stream << thrust << endl;

    file.close();
}

void Thruster::Load(QString fileName) {
    QFile file = QFile(fileName);
    bool success = file.open(QIODevice::ReadOnly);

    if (!success) {
        return;
    }

    QTextStream stream = QTextStream(&file);
    QString value = stream.readLine();
    thrust = value.toFloat();

    file.close();
}
