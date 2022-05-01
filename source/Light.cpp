#include "Light.hpp"


Light::Light(float field_of_view, float density):
    FieldOfView(field_of_view), Density(density)
{

}


void Light::DrawLight(sf::RenderWindow* window, const std::vector<LineSegment*>& walls, \
                      const Vector2d& position, const Vector2d& sight_direction)
{
    Vector2d sight = sight_direction;
    float step = 1 / Density;
    for(float angle = - FieldOfView / 2; angle <= FieldOfView / 2; angle += step){

        sight.rotate(angle, position);

        DrawRay(window, walls, position, sight);

        sight = sight_direction;
    }
}


void Light::DrawRay(sf::RenderWindow* window, const std::vector<LineSegment*>& walls, \
                      const Vector2d& position, const Vector2d& sight)
{
    Vector2d new_point;
    Vector2d closest;
    float distance;
    float min_distance = WIDTH;
    for(auto& wall: walls){
        new_point = LineSegment::Intersection(position, sight, wall);
        if(new_point.x != -1 && new_point.y != -1){
            distance = Vector2d::Distance(position, new_point);
            if(distance < min_distance){
                min_distance = distance;
                closest = new_point;
            }
        }
    }
    sf::Vertex line[] = {
        sf::Vertex(position),
        sf::Vertex(closest)
    };
    window->draw(line, 2, sf::Lines);
}

