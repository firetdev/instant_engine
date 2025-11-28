// Instant namespace file
// Contains helper functions and classes

#pragma once

#include <iostream>
#include <cmath>

namespace Instant {
inline float delta;

class Vector2 {
public:
    float x;
    float y;

    // Constructors
    Vector2() : x(0.f), y(0.f) {}
    Vector2(float x, float y) : x(x), y(y) {}

    // Vector addition
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // Vector subtraction
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // Scalar multiplication
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // Scalar division
    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    // Magnitude (length) of the vector
    float length() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalize the vector (make it length 1)
    Vector2 normalized() const {
        float len = length();
        return len != 0 ? (*this / len) : Vector2(0, 0);
    }

    // Print the vector (for debugging)
    void print() const {
        std::cout << "Vector2(" << x << ", " << y << ")\n";
    }
};

inline Vector2 gravity = {0, 100};
}
