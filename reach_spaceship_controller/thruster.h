#ifndef THRUSTER_H
#define THRUSTER_H
#include "isavable.h"

/// Represents a thruster of the spaceship's navigation module.
class Thruster : public ISavable {
private:
    float thrust;

public:
    Thruster();

    /// Returns the thrust of the thruster.
    float GetThrust() const;

    /// Sets the thrust of the thruster
    void SetThrust(float thrust);

    /// Saves the thrust to a file.
    virtual void Save(QString fileName) override;

    /// Loads the thrust from a file.
    virtual void Load(QString fileName) override;
};

#endif // THRUSTER_H
