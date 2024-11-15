#ifndef PLANET_H
#define PLANET_H

#include <QVector2D>  // Using QVector2D for position

class Planet {
protected:
    QString name;  // Name of the planet
    QVector2D position;  // Position using QVector2D (x, y)

public:
    // Constructor that initializes the planet's name and position
    Planet(const QString &name, float x = 0.0f, float y = 0.0f);

    // Getter for the planet's name
    QString GetName() const;

    // Getter for the planet's position as a QVector2D
    QVector2D GetPosition() const;

    // Virtual destructor for proper cleanup in derived classes
    virtual ~Planet() = default;
};

#endif // PLANET_H
