#pragma once
#pragma once

#include <cmath>
#include <ostream>

#include <SFML/System/Vector2.hpp>


struct Vector2 {
    float x;
    float y;

    Vector2() { x = 0, y = 0; }
    Vector2(float X, float Y) { x = X, y = Y; }
    Vector2(const Vector2& v) { x = v.x, y = v.y; }
    Vector2(const sf::Vector2f& v) { x = v.x, y = v.y; }

    float getModule() const { return std::sqrt(x * x + y * y); }
    Vector2& normalize();
    Vector2& rotate(float angle, Vector2 point = { 0, 0 });

    operator sf::Vector2f() const { return sf::Vector2f(x, y); }

    Vector2& operator+=(const Vector2& v);
    Vector2& operator-=(const Vector2& v);

    friend Vector2 operator*(const Vector2& v, float k) { return Vector2(v.x * k, v.y * k); }
    friend Vector2 operator*(float k, const Vector2& v) { return Vector2(v.x * k, v.y * k); }
    friend Vector2 operator-(const Vector2& v) { return Vector2(-v.x, -v.y); }

    friend Vector2 operator+(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x + v2.x, v1.y + v2.y); }
    friend Vector2 operator-(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x - v2.x, v1.y - v2.y); }

    friend bool operator ==(const Vector2& v1, const Vector2& v2) { return (v1.x == v2.x) && (v1.y == v2.y); }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v);

    static float DotProduct(const Vector2& v1, const Vector2& v2) { return v1.x * v2.x + v1.y * v2.y; }
    static float Distance(const Vector2& v1, const Vector2& v2) { return std::sqrt(powf(v1.x - v2.x, 2) + powf(v1.y - v2.y, 2)); }
    static Vector2 Reflect(const Vector2& ToReflect, const Vector2& v);
};

