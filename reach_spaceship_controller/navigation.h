#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "isavable.h"
#include "thruster.h"
#include <QVector2D>

const float THRUST_POWER = 500.f;
const float EARTH_RADIUS = 6.371e6f;

/// Represents the navigation module of the spcaeship.
class Navigation : public ISavable {
private:
    Thruster* thrusterX;
    Thruster* thrusterY;

public:
    /// The position of the spaceship.
    QVector2D Position;

    /// The direction the spaceship is going.
    QVector2D Direction;

    /// The current velocity of the spaceship.
    QVector2D Velocity;

    /// The current acceleration of the spaceship.
    QVector2D Acceleration;

    Navigation();
    ~Navigation();

    /// Returns a reference to the X thruster of the navigation module.
    Thruster& ThrusterX();

    /// Returns a reference to the Y thruster of the navigation module.
    Thruster& ThrusterY();

    /// Applies the thrust values to velocity of the spaceship.
    void ApplyThrust(float mass, float deltaTime);

    /// Saves all navigation data to a file.
    virtual void Save(QString fileName) override;

    /// Loads all navigation data from a file.
    virtual void Load(QString fileName) override;
};

#endif // NAVIGATION_H
