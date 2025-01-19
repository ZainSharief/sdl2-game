#ifndef VEC2_H
#define VEC2_H

#include <cmath>

struct vec2 {
    float x, y;

    vec2(float x = 0, float y = 0) : x(x), y(y) {}

    // Override '+' with vec2 operations
    vec2 operator+(const vec2& other) const {
        return vec2(x + other.x, y + other.y);
    }
    vec2 operator+(const float other) const {
        return vec2(x + other, y + other);
    }

    // Override '-' with vec2 operations
    vec2 operator-(const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }
    vec2 operator-(const float other) const {
        return vec2(x - other, y - other);
    }

    // Override '*' with vec2 operations
    vec2 operator*(const vec2& other) const {
        return vec2(x * other.x, y * other.y);
    }
    vec2 operator*(const float other) const {
        return vec2(x * other, y * other);
    }

    // Override '/' with vec2 operations
    vec2 operator/(const vec2& other) const {
        return vec2(
            other.x == 0 ? x / 1e-8 : x / other.x,     
            other.y == 0 ? y / 1e-8 : y / other.y       
        );
    }
    vec2 operator/(const float other) const {
        return other == 0 ? vec2(x / 1e-8, y / 1e-8) : vec2(x / other, y / other);
    }

    // Normalise to a unit vector
    vec2 normalize() const {
        float magnitude = std::sqrt(x*x + y*y);
        return magnitude > 0 ? *this / magnitude : vec2(0, 0);
    }

    // Compute a dot product between vectors
    float dot(const vec2& other) const {
        return x * other.x + y * other.y;
    }

    // Compute the cross product between vectors
    float cross(const vec2& other) const {
        return x * other.y - y * other.x;
}
};

#endif