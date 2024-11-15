#ifndef SIMULATION_H
#define SIMULATION_H
#include "spaceship.h"
#include "earth.h"

/// Class that handles the interaction between the spaceship and the earth.
class Simulation {
private:
    Spaceship* spaceship;
    Earth* earth;

    // Use values from earth and spacehip to calculate the gravitational acceleration.
    QVector2D CalculateGravitationalAcceleration();

public:
    Simulation();
    ~Simulation();

    /// Returns the spaceship object that is part of the simulation.
    Spaceship& GetSpaceship();

    /// Returns the earth object that is part of the simulation.
    Earth& GetEarth();

    /// Updates the spaceship's orbit based on the earth's gravity
    void Update(float deltaTime, float simulationSpeed);
};

#endif // SIMULATION_H
