#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {

public:
    /// The X coordinate of the vector.
    float X;

    /// The Y coordinate of the vector.
    float Y;

    /// Creates a new zero vector (0, 0).
    Vector2();

    /// Creates a new vector with the specified coordinates.
    Vector2(float x, float y);

    /// Returns the magnitude/length of the vector.
    float Magnitude();

    /// Returns the distance between the vector and another vector.
    float Distance(Vector2& other);

    /// Returns the vector in a normalized state.
    Vector2 Normalized();

    Vector2 operator +(Vector2& other);
    Vector2 operator -(Vector2& other);
    Vector2& operator +=(Vector2& other);
    Vector2& operator -=(Vector2& other);
    Vector2 operator *(float scalar);
    Vector2& operator *=(float scalar);
    Vector2& operator =(Vector2& other);
    bool operator ==(const Vector2& other) const;

};

Vector2 operator *(float scalar, Vector2& vector);

#endif // VECTOR2_H
