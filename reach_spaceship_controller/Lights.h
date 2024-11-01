#ifndef LIGHTS_H
#define LIGHTS_H


class Lights
{
private:
    bool turnedOn;
public:
    Lights();
    void turnOff();
    void turnOn();
    bool isOn();

};

#endif // LIGHTS_H
