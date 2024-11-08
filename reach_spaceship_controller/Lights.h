#ifndef LIGHTS_H
#define LIGHTS_H

#include "isavable.h"

class Lights: public ISavable
{
private:
    bool turnedOn;
public:
    Lights();
    void turnOff();
    void turnOn();
    bool isOn();

    virtual void Save(QString fileName) override;

    virtual void Load(QString fileName) override;
};

#endif // LIGHTS_H
