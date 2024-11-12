#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "isavable.h"
#include <QVector2D>

/// Represents the navigation module of the spcaeship.
class Navigation : public ISavable {
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

    /// Applies the thrust values to velocity of the spaceship.
    void ApplyThrust(float mass, float deltaTime);

    /// Saves all navigation data to a file.
    virtual void Save(QString fileName) override;

    /// Loads all navigation data from a file.
    virtual void Load(QString fileName) override;
};

#endif // NAVIGATION_H
