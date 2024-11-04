#include "hull.h"
#include <QFile>
#include <QTextStream>

using namespace Qt;

Hull::Hull() {
    integrity = 100.f;
}

float Hull::GetIntegrity() {
    return integrity;
}

void Hull::SetIntegrity(float integrity) {
    this->integrity = qBound(0.f, integrity, 100.f);
}

void Hull::Save(QString fileName) {
    QFile file = QFile(fileName);
    file.open(QIODevice::WriteOnly);

    QTextStream stream = QTextStream(&file);
    stream << integrity << endl;

    file.close();
}

void Hull::Load(QString fileName) {
    QFile file = QFile(fileName);
    bool success = file.open(QIODevice::ReadOnly);

    if (!success) {
        return;
    }

    QTextStream stream = QTextStream(&file);
    QString value = stream.readLine();
    SetIntegrity(value.toFloat());

    file.close();
}

