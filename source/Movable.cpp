#include "Movable.hpp"


Movable::Movable(const Vector2d& position,  const Vector2d& direction):
    Position(position),  Direction(direction)
{

}


inline void Movable::Move(const sf::Time& dt)
{
    Position += dt.asSeconds() * MOVE_SPEED * Direction;
}


inline void Movable::setDirection(const Vector2d& direction)
{
    Direction = direction;
}

