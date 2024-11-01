#ifndef ISAVABLE_H
#define ISAVABLE_H

#include <QString>

/// Interface with methods for saving and loading.
class ISavable {
public:
    virtual void Save(QString fileName) = 0;
    virtual void Load(QString fileName) = 0;
};

#endif // ISAVABLE_H
