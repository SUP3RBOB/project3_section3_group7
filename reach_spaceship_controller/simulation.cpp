#include "simulation.h"

const float EARTH_GRAVITY = 6.67430e-11f;

Simulation::Simulation() {
    spaceship = new Spaceship();
    earth = new Earth("Earth", 0.f, 0.f, 5.972e24f, 6.371e6f);
}

Simulation::~Simulation() {
    delete spaceship;
    delete earth;
}

Spaceship &Simulation::GetSpaceship() {
    return (*spaceship);
}

Earth &Simulation::GetEarth() {
    return (*earth);
}

QVector2D Simulation::CalculateGravitationalAcceleration() {
    QVector2D direction = earth->GetPosition() - spaceship->GetNavigation().Position;
    float distance = direction.length();
    float accelerationMagnitude = (EARTH_GRAVITY * earth->GetMass()) / (distance * distance);
    return direction.normalized() * accelerationMagnitude;
}

void Simulation::Update(float deltaTime, float simulationSpeed) {
    Navigation& nav = spaceship->GetNavigation();

    // update delta time based on the simulation speed
    deltaTime *= simulationSpeed;

    // Apply gravity and thrust to the acceleration
    QVector2D gravityAccel = CalculateGravitationalAcceleration();
    QVector2D thrustAccel = nav.Direction * (THRUST_POWER / spaceship->GetMass());
    nav.Acceleration = gravityAccel + thrustAccel;

    // Update velocity and position
    nav.Velocity = nav.Velocity + nav.Acceleration * deltaTime;
    nav.Position = nav.Position + nav.Velocity * deltaTime;
}