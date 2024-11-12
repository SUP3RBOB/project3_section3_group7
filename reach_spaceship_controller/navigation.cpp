#include "navigation.h"
#include <QFile>
#include <QTextStream>

using namespace Qt;

const float EARTH_RADIUS = 6.371e6f;
const float THRUST_POWER = 5000.f;

Navigation::Navigation() {
    QVector2D Position = QVector2D(0.f, EARTH_RADIUS + 1000000.f);
    QVector2D Direction = QVector2D();
    QVector2D Velocity = QVector2D();
    QVector2D Acceleration = QVector2D();
}

void Navigation::ApplyThrust(float mass, float deltaTime) {
    Direction.setX(0.f);
    Direction.setY(0.f);

    QVector2D accel = Direction * (THRUST_POWER / mass);
    Velocity += accel * deltaTime;
}

void Navigation::Save(QString fileName) {
    QFile file = QFile(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream = QTextStream(&file);
        stream << Position.x() << endl;
        stream << Position.y() << endl;
        stream << Direction.x() << endl;
        stream << Direction.y() << endl;
        stream << Velocity.x() << endl;
        stream << Velocity.y() << endl;
        stream << Acceleration.x() << endl;
        stream << Acceleration.y() << endl;

        file.close();
    }
}

void Navigation::Load(QString fileName) {
    QFile file = QFile(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream = QTextStream(&file);

        Position.setX(stream.readLine().toFloat());
        Position.setY(stream.readLine().toFloat());
        Direction.setX(stream.readLine().toFloat());
        Direction.setY(stream.readLine().toFloat());
        Velocity.setX(stream.readLine().toFloat());
        Velocity.setY(stream.readLine().toFloat());
        Acceleration.setX(stream.readLine().toFloat());
        Acceleration.setY(stream.readLine().toFloat());

        file.close();
    }
}
