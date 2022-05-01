#include "LightSource.hpp"


LightSource::LightSource(const Vector2d& position, const Vector2d& sight_direction, float field_of_view, float density):
    Movable(position, {0, 0}), MyLight(field_of_view, density), SightDirection(sight_direction), Radius(3), ToDraw(Radius)
{

}


void LightSource::MoveWithCollision(const sf::Time& dt, const std::vector<LineSegment*>& walls)
{
    Move(dt);

    float distance;
    float min_distance;
    for(auto& wall: walls){
        distance = wall->Distance(Position);
        min_distance = Radius + wall->getThickness() / 2;
        if(distance < min_distance){
            Vector2d normal = 1 / wall->getNormalModule() * wall->getNormal();
            if(wall->Orientation(Position) == 1)
                normal = -normal;
            normal = (min_distance - distance) * normal;
            if(wall->isBelong(Position - normal))
                Position += normal;
        }
    }
}


void LightSource::Draw(sf::RenderWindow* window, const std::vector<LineSegment*>& walls)
{
    MyLight.DrawLight(window, walls, Position, SightDirection);

    ToDraw.setPosition(Position.x - Radius, Position.y - Radius);
    window->draw(ToDraw);
}
