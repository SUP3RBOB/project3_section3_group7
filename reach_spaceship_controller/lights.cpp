#include "lights.h"

Lights::Lights() {
    this->turnedOn = false;
}

void Lights::turnOff(){
    turnedOn = false;
}
void Lights::turnOn(){
    turnedOn = true;
}
bool Lights::isOn(){
    return(turnedOn);
}


