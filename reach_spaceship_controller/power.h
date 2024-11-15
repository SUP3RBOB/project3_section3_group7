#ifndef POWER_H
#define POWER_H

#include <QString>
#include "isavable.h"
#include <QObject>

// The Power class represents the power module in a spaceship, implementing
// the ISavable interface to allow saving/loading its state to/from a file.
class Power : public QObject, public ISavable {
private:
    Q_OBJECT

    float power;         // Current power level (0.0 to 100.0, or as appropriate)
    bool on;             // Power on/off status

public:
    // Constructor initializes the power level with an optional parameter.
    // By default, it sets the power level to 0.0 and the power status to off.
    Power(float initialPower = 0.0f);

    // Destructor
    ~Power();

    // Accessor for the power level.
    // Returns the current power level.
    float GetPower() const;

    // Accessor for the power status.
    // Returns true if power is on, false if off.
    bool IsOn() const;

    // Mutator for the power level.
    // Sets the power to the specified level.
    void SetPower(float level);

    // Mutator for the power status.
    // Sets the power on/off status.
    void SetOn(bool status);

    // Saves the power state (on/off and power level) to a file.
    virtual void Save(QString fileName) override;

    // Loads the power state (on/off and power level) from a file.
    virtual void Load(QString fileName) override;

signals:
    void OnPowerActivated(bool on);
};

#endif // POWER_H
