#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "power.h"
#include "Lights.h"
#include "comms.h"
#include "lifesupport.h"
#include "hull.h"

class Spaceship {
private:
    float mass;

    Power* power;
    Lights* lights;
    LifeSupport* lifeSupport;
    Communication* communication;
    Hull* hull;

public:
    Spaceship();
    ~Spaceship();

    float GetMass() const;

    Power& GetPower();
    Lights& GetLights();
    LifeSupport& GetLifeSupport();
    Communication& GetComms();
    Hull& GetHull();

    void Save();
    void Load();
};

#endif // SPACESHIP_H
