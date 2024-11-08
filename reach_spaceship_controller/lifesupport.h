#ifndef LIFESUPPORT_H
#define LIFESUPPORT_H
#include "isavable.h"

/// Represents the life support module of the spaceship.
class LifeSupport : public ISavable {
private:
    float oxygen;
    float temperature;

public:
    LifeSupport(float oxygen, float temperature);

    /// Returns the oxygen levels of the spaceship.
    float GetOxygen();

    /// Sets the oxygen levels of the spacehip.
    void SetOxygen(float oxygen);

    /// Returns the temperature (celsius) of the spaceship.
    float GetTemp();

    /// Sets the temperature (celsius) of the spaceship.
    void SetTemp(float temperature);

    /// Returns the temperature in Fahrenheit.
    float GetTempAsF();

    /// Returns the temperature in Kelvin.
    float GetTempAsK();

    /// Saves the life support values to a file.
    virtual void Save(QString fileName) override;

    /// Loads the life support values from a file.
    virtual void Load(QString fileName) override;
};

#endif // LIFESUPPORT_H
