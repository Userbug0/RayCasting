#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2d.hpp"
#include "LineSegment.hpp"
#include "Settings.hpp"


class Movable
{
public:
    Movable(const Vector2d& position, const Vector2d& direction);
    virtual ~Movable() = default;

    virtual void Move(const sf::Time& dt);
    virtual void setDirection(const Vector2d& direction);

protected:
    Vector2d Position;
    float MoveSpeed;
    Vector2d Direction;

};

