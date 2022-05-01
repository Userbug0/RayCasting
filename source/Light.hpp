#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2d.hpp"
#include "LineSegment.hpp"
#include "Settings.hpp"


class Light
{
public:
    Light(float field_of_view, float density);
    ~Light() = default;

    void DrawLight(sf::RenderWindow* window, const std::vector<LineSegment*>& walls, \
                   const Vector2d& position, const Vector2d& sight_direction);
private:
    float FieldOfView;
    float Density;

    void DrawRay(sf::RenderWindow* window, const std::vector<LineSegment*>& walls, \
        const Vector2d& position, const Vector2d& sight_direction);
};

