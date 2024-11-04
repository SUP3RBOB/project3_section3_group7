#ifndef HULL_H
#define HULL_H

#include "isavable.h"

// The hull module of the spaceship.
class Hull : public ISavable {
private:
    float integrity;

public:
    /// Creates a new hull module with max integrity (100%).
    Hull();

    /// Returns the hull integrity.
    float GetIntegrity();

    /// Sets the hull integrity.
    void SetIntegrity(float integrity);

    /// Saves the hull integrity to a file.
    virtual void Save(QString fileName) override;

    /// Loads the hull integrity from a file.
    virtual void Load(QString fileName) override;
};

#endif // HULL_H
