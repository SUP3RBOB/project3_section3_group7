#include "navigation.h"
#include <QFile>
#include <QTextStream>

using namespace Qt;

const float EARTH_RADIUS = 6.371e6f;
const float THRUST_POWER = 5000.f;

Navigation::Navigation() {
    Position = QVector2D(0.f, EARTH_RADIUS + 1000000.f);
    Direction = QVector2D();
    Velocity = QVector2D();
    Acceleration = QVector2D();
}

Navigation::~Navigation() {

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
        stream << Position.x() << "," << Position.y() << endl;
        stream << Direction.x() << "," << Direction.y() << endl;
        stream << Velocity.x() << "," << Velocity.y() << endl;
        stream << Acceleration.x() << "," << Acceleration.y() << endl;

        file.close();
    }
}

void Navigation::Load(QString fileName) {
    QFile file = QFile(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream = QTextStream(&file);

        QStringList values = stream.readLine().split(",");
        Position.setX(values[0].toFloat());
        Position.setY(values[1].toFloat());

        values = stream.readLine().split(",");
        Direction.setX(values[0].toFloat());
        Direction.setY(values[1].toFloat());

        values = stream.readLine().split(",");
        Velocity.setX(values[0].toFloat());
        Velocity.setY(values[1].toFloat());

        values = stream.readLine().split(",");
        Acceleration.setX(values[0].toFloat());
        Acceleration.setY(values[1].toFloat());

        file.close();
    }
}
