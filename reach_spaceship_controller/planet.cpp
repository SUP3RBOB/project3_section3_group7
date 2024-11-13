#include "Planet.h"

// Constructor to initialize name and position
Planet::Planet(const QString &name, float x, float y) noexcept
    : name(name), position(x, y) {}

// Getter for the planet's name
QString Planet::GetName() const noexcept {
    return name;
}

// Getter for the planet's position, returns Position struct
Planet::Position Planet::GetPosition() const noexcept {
    return position;
}
