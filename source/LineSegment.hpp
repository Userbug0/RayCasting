#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2d.hpp"


class LineSegment
{
public:
    Vector2d Point1;
    Vector2d Point2;

    LineSegment(const Vector2d& point1, const Vector2d& point2, int thickness, const sf::Color& color);
    ~LineSegment() = default;

    void Draw(sf::RenderWindow* window);
    // 0 --> p, q and r are collinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    int Orientation(const Vector2d& point);
    bool isBelong(const Vector2d& point);
    float Distance(const Vector2d& point);

    int getThickness() const {return Thickness;}
    Vector2d getNormal() const {return Normal;}
    float getNormalModule() const {return NormalModule;}

    // return Vector2d(-1, -1) if no intersection
    static Vector2d Intersection(const Vector2d& p1, const Vector2d& p2, const LineSegment* line);

private:
    // ax + by + c = 0
    float a, b, c;
    Vector2d Normal;
    float NormalModule;

    int Thickness;
    sf::Color Color;
    sf::Vertex ToDraw[4];
};

