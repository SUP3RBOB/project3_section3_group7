#include "navigation.h"
#include <QFile>
#include <QTextStream>

using namespace Qt;

const float EARTH_RADIUS = 6.371e6f;

Navigation::Navigation() {
    thrusterX = new Thruster();
    thrusterY = new Thruster();

    Position = QVector2D(0.f, EARTH_RADIUS + 1000000.f);
    Direction = QVector2D();
    Velocity = QVector2D();
    Acceleration = QVector2D();
}

Navigation::~Navigation() {
    delete thrusterX;
    delete thrusterY;
}

Thruster& Navigation::ThrusterX() {
    return (*thrusterX);
}

Thruster& Navigation::ThrusterY() {
    return (*thrusterY);
}

void Navigation::ApplyThrust(float mass, float deltaTime) {
    Direction.setX(thrusterX->GetThrust());
    Direction.setY(thrusterY->GetThrust());

    QVector2D acceleration = Direction * (THRUST_POWER / mass);
    Velocity += acceleration * deltaTime;
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

    thrusterX->Save("thruster_x.txt");
    thrusterY->Save("thruster_y.txt");
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

    thrusterX->Load("thruster_x.txt");
    thrusterY->Load("thruster_y.txt");
}
