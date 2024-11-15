#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "navigation.h"
#include "power.h"
#include "Lights.h"
#include "comms.h"
#include "lifesupport.h"
#include "hull.h"
#include "map.h"

/// Represents a spaceship with all of its parts.
class Spaceship {
private:
    float mass;

    Navigation* navigation;
    Power* power;
    Lights* lights;
    LifeSupport* lifeSupport;
    Communication* communication;
    Hull* hull;
    Map* map;

public:
    Spaceship();
    ~Spaceship();

    /// Returns the mass of the spaceship.
    float GetMass() const;

    /// Returns the navigation module of the spaceship.
    Navigation& GetNavigation();

    /// Returns the power module of the spaceship.
    Power& GetPower();

    /// Returns the lights module of the spaceship.
    Lights& GetLights();

    /// Returns the life support module of the spaceship.
    LifeSupport& GetLifeSupport();

    /// Returns the communication module of the spaceship.
    Communication& GetComms();

    /// Returns the hull module of the spaceship.
    Hull& GetHull();

    /// Returns the map module of the spaceship.
    Map& GetMap();

    /// Saves the data of all modules in the spaceship.
    void Save();

    /// Loads the data of all modules in the spacehsip.
    void Load();
};

#endif // SPACESHIP_H
