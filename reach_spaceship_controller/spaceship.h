#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "power.h"
#include "Lights.h"
#include "comms.h"
#include "lifesupport.h"
#include "hull.h"

class Spaceship : public QObject {
private:
    Q_OBJECT

    Power power = Power(100.f);
    Lights lights;
    LifeSupport lifeSupport;
    Communication communication = Communication();
    Hull hull;

private slots:
    void PowerActivated(bool isOn);

public:
    Spaceship();
    ~Spaceship();

    Power& GetPower();
    Lights& GetLights();
    LifeSupport& GetLifeSupport();
    Communication& GetComms();
    Hull& GetHull();

    void Save();
    void Load();
};

#endif // SPACESHIP_H
