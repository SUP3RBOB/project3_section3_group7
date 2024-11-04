#ifndef HULL_H
#define HULL_H

#include "isavable.h"

class Hull : public ISavable {
private:
    float integrity;

public:
    Hull();

    float GetIntegrity();
    void SetIntegrity(float integrity);

    virtual void Save(QString fileName) override;
    virtual void Load(QString fileName) override;
};

#endif // HULL_H
