#include "spaceship.h"
#include <QDebug>

Spaceship::Spaceship() {
    power = new Power(100.f);
    lights = new Lights();
    lifeSupport = new LifeSupport(100.f, 22.f);
    hull = new Hull();

    connect(power, &Power::OnPowerActivated, this, &Spaceship::PowerActivated);
}

Spaceship::~Spaceship() {
    delete power;
    delete lights;
    delete lifeSupport;
    delete communication;
    delete hull;
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

void Spaceship::Save() {
    power->Save("power.txt");
    lights->Save("lights.txt");
    communication->Save("comms.txt");
    lifeSupport->Save("lifesupport.txt");
    hull->Save("hull.txt");
}

void Spaceship::Load() {
    power->Load("power.txt");
    lights->Load("lights.txt");
    communication->Load("comms.txt");
    lifeSupport->Load("lifesupport.txt");
    hull->Load("hull.txt");
}

void Spaceship::PowerActivated(bool isOn) {
    if (isOn) {
        lights->Load("lights.txt");
    } else {
        lights->Save("lights.txt");
        lights->turnOff();
    }
}
