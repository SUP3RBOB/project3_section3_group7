#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "navigation.h"
#include "power.h"
#include "Lights.h"
#include "comms.h"
#include "lifesupport.h"
#include "hull.h"

class Spaceship {
private:
    float mass;

    Navigation* navigation;
    Power* power;
    Lights* lights;
    LifeSupport* lifeSupport;
    Communication* communication;
    Hull* hull;

public:
    Spaceship();
    ~Spaceship();

    float GetMass() const;

    Navigation& GetNavigation();
    Power& GetPower();
    Lights& GetLights();
    LifeSupport& GetLifeSupport();
    Communication& GetComms();
    Hull& GetHull();

    void Save();
    void Load();
};

#endif // SPACESHIP_H
