#ifndef EARTH_H
#define EARTH_H

#include "Planet.h"

// Earth class that inherits from Planet and defines mass and radius for Earth
class Earth : public Planet {
private:
    float mass;    // Earth's mass
    float radius;  // Earth's radius

public:
    // Constructor that sets Earth's name, position, mass, and radius
    Earth(const QString &name, float x, float y, float mass, float radius);

    // Returns Earth's mass
    float GetMass() const;

    // Returns Earth's radius
    float GetRadius() const;
};

#endif // EARTH_H
