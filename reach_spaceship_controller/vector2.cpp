#include "vector2.h"
#include <QtCore/QtMath>

Vector2::Vector2() {
    X = 0.f;
    Y = 0.f;
}

Vector2::Vector2(float x, float y) {
    X = x;
    Y = y;
}

float Vector2::Magnitude() {
    return qSqrt((X * X) + (Y * Y));
}

float Vector2::Distance(Vector2& other) {
    return qSqrt(qPow(X - other.X, 2.f) + qPow(Y - other.Y, 2.f));
}

Vector2 Vector2::Normalized() {
    float magnitude = Magnitude();
    return Vector2(X / magnitude, Y / magnitude);
}

Vector2 Vector2::operator +(Vector2& other) {
    X += other.X;
    Y += other.Y;
    return Vector2(X, Y);
}

Vector2 Vector2::operator -(Vector2& other) {
    X -= other.X;
    Y -= other.Y;
    return Vector2(X, Y);
}

Vector2& Vector2::operator +=(Vector2& other) {
    X += other.X;
    Y += other.Y;
    return (*this);
}

Vector2& Vector2::operator -=(Vector2& other) {
    X -= other.X;
    Y -= other.Y;
    return (*this);
}

Vector2 Vector2::operator *(float scalar) {
    X *= scalar;
    Y *= scalar;
    return Vector2(X, Y);
}

Vector2& Vector2::operator *=(float scalar) {
    X *= scalar;
    Y *= scalar;
    return (*this);
}

Vector2 operator *(float scalar, Vector2& vector) {
    return Vector2(vector.X * scalar, vector.Y * scalar);
}

Vector2& Vector2::operator =(Vector2& other) {
    X = other.X;
    Y = other.Y;
    return (*this);
}

bool Vector2::operator ==(const Vector2& other) const {
    return X == other.X && Y == other.Y;
}
