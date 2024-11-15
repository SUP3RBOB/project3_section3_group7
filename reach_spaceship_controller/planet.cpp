#include "Planet.h"

// Constructor to initialize name and position
Planet::Planet(const QString &name, float x, float y)
    : name(name), position(x, y) {}

// Getter for the planet's name
QString Planet::GetName() const {
    return name;
}

// Getter for the planet's position, returns QVector2D
QVector2D Planet::GetPosition() const {
    return position;
}
