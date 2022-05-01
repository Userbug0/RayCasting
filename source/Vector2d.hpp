#pragma once

#include <math.h>
#include <ostream>

#include <SFML/System/Vector2.hpp>


struct Vector2d{
    float x;
    float y;

    Vector2d(){x = 0, y = 0;}
    Vector2d(float X, float Y) { x = X, y = Y;}
    Vector2d(const Vector2d& v) {x = v.x, y = v.y;}
    Vector2d(const sf::Vector2f& v) {x = v.x, y = v.y;}

    float getModule() const {return powf(x * x + y * y, 0.5);}
    Vector2d& normalize();
    Vector2d& rotate(float angle, Vector2d point = {0, 0});

    operator sf::Vector2f() const {return sf::Vector2f(x, y);}

    Vector2d& operator+=(const Vector2d& v);
    Vector2d& operator-=(const Vector2d& v);

    friend Vector2d operator*(float k, const Vector2d& v){return Vector2d(v.x * k, v.y * k); }
    friend Vector2d operator-(const Vector2d& v){return Vector2d(-v.x, -v.y);}

    friend Vector2d operator+(const Vector2d& v1, const Vector2d& v2){return Vector2d(v1.x + v2.x, v1.y + v2.y);}
    friend Vector2d operator-(const Vector2d& v1, const Vector2d& v2){return Vector2d(v1.x - v2.x, v1.y - v2.y);}

    friend bool operator ==(const Vector2d& v1, const Vector2d& v2) {return (v1.x == v2.x) && (v1.y == v2.y);}

    friend std::ostream& operator<<(std::ostream& os, const Vector2d& v);

    static float DotProduct(const Vector2d& v1, const Vector2d& v2) {return v1.x * v2.x + v1.y * v2.y;}
    static float Distance(const Vector2d& v1, const Vector2d& v2) {return powf(powf(v1.x - v2.x, 2) + powf(v1.y - v2.y, 2), 0.5);}
    static Vector2d Reflect(const Vector2d& ToReflect, const Vector2d& v);
};

