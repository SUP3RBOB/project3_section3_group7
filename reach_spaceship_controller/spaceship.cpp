#include "spaceship.h"
#include <QDebug>

Spaceship::Spaceship() {
    mass = 1000.f;

    navigation = new Navigation();
    power = new Power(100.f);
    lights = new Lights();
    lifeSupport = new LifeSupport(100.f, 22.f);
    communication = new Communication();
    hull = new Hull();
    map = new Map();
}

Spaceship::~Spaceship() {
    delete navigation;
    delete power;
    delete lights;
    delete lifeSupport;
    delete communication;
    delete hull;
    delete map;
}

float Spaceship::GetMass() const {
    return mass;
}

Navigation& Spaceship::GetNavigation() {
    return (*navigation);
}

Power& Spaceship::GetPower() {
    return (*power);
}

Lights& Spaceship::GetLights() {
    return (*lights);
}

LifeSupport& Spaceship::GetLifeSupport() {
    return (*lifeSupport);
}

Communication& Spaceship::GetComms() {
    return (*communication);
}

Hull& Spaceship::GetHull() {
    return (*hull);
}

Map &Spaceship::GetMap() {
    return (*map);
}

void Spaceship::Save() {
    navigation->Save("navigation.txt");
    power->Save("power.txt");
    lights->Save("lights.txt");
    communication->Save("comms.txt");
    lifeSupport->Save("lifesupport.txt");
    hull->Save("hull.txt");
}

void Spaceship::Load() {
    navigation->Load("navigation.txt");
    power->Load("power.txt");
    lights->Load("lights.txt");
    communication->Load("comms.txt");
    lifeSupport->Load("lifesupport.txt");
    hull->Load("hull.txt");
}
