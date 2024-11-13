#ifndef PLANET_H
#define PLANET_H

#include <QString>
#include <string>

class Planet {
protected:
    QString name;

    // Internal struct for 2D position, representing the position as specified in UML
    struct Position {
        float x = 0.0f;
        float y = 0.0f;

        // Constructor with default parameters
        constexpr Position(float x = 0.0f, float y = 0.0f) noexcept : x(x), y(y) {}

        // Convert position to a string (useful for debugging)
        std::string ToString() const {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        }
    };

    Position position;

public:
    // Constructor that initializes the planet's name and position
    explicit Planet(const QString &name, float x = 0.0f, float y = 0.0f) noexcept;

    // Virtual methods for mass and radius to be overridden by derived classes
    virtual float GetMass() const noexcept = 0;
    virtual float GetRadius() const noexcept = 0;

    // Getter for the planet's name
    QString GetName() const noexcept;

    // Getter for the planet's position as a Position struct
    Position GetPosition() const noexcept;

    // Virtual destructor
    virtual ~Planet() noexcept = default;
};

#endif // PLANET_H
