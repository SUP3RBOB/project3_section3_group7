#include "lifesupport.h"
#include <QtMath>
#include <QFile>
#include <QTextStream>

using namespace Qt;

LifeSupport::LifeSupport() {
    this->oxygen = 0.f;
    this->temperature = 0.f;
}

LifeSupport::LifeSupport(float oxygen, float temperature) {
    this->oxygen = oxygen;
    this->temperature = temperature;
}

float LifeSupport::GetOxygen() {
    return oxygen;
}

void LifeSupport::SetOxygen(float oxygen) {
    this->oxygen = qMax(oxygen, 0.f);
}

float LifeSupport::GetTemp() {
    return temperature;
}

void LifeSupport::SetTemp(float temperature) {
    this->temperature = temperature;
}

float LifeSupport::GetTempAsF() {
    return (temperature * 9.f / 5.f) + 32.f;
}

float LifeSupport::GetTempAsK() {
    const float TO_KELVIN = 273.15f;
    return temperature + TO_KELVIN;
}

void LifeSupport::Save(QString fileName) {
    QFile file = QFile(fileName);
    file.open(QIODevice::WriteOnly);

    QTextStream stream = QTextStream(&file);
    stream << oxygen << endl;
    stream << temperature << endl;

    file.close();
}

void LifeSupport::Load(QString fileName) {
    QFile file = QFile(fileName);
    bool success = file.open(QIODevice::ReadOnly);

    if (!success) {
        return;
    }

    QTextStream stream = QTextStream(&file);
    oxygen = stream.readLine().toFloat();
    temperature = stream.readLine().toFloat();

    file.close();
}
