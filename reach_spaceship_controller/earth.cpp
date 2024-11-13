#include "Earth.h"

// Constructor to initialize Earth's name, position, mass, and radius
Earth::Earth(const QString &name, float x, float y, float mass, float radius)
    : Planet(name, x, y), mass(mass), radius(radius) {}

// Returns Earth's mass
float Earth::GetMass() const noexcept {
    return mass;
}

// Returns Earth's radius
float Earth::GetRadius() const noexcept {
    return radius;
}
