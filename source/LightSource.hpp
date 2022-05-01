#pragma once

#include <SFML/Graphics.hpp>

#include "Light.hpp"
#include "LineSegment.hpp"
#include "Vector2d.hpp"
#include "Movable.hpp"


class LightSource: public Movable
{
public:
    LightSource(const Vector2d& position, const Vector2d& sight_direction, float field_of_view, float density);
    virtual ~LightSource() = default;

    void Draw(sf::RenderWindow* window, const std::vector<LineSegment*>& walls);
    void MoveWithCollision(const sf::Time& dt, const std::vector<LineSegment*>& walls);

    void LookAt(const Vector2d& point) { SightDirection = point; }

private:
    Light MyLight;
    Vector2d SightDirection;

    float Radius;
    sf::CircleShape ToDraw;
};

