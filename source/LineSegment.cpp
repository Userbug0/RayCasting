#include "LineSegment.hpp"


LineSegment::LineSegment(const Vector2d& point1, const Vector2d& point2, int thickness, const sf::Color& color):
    Point1(point1), Point2(point2), Thickness(thickness), Color(color)
{
    a = Point1.y - Point2.y;
    b = Point2.x - Point1.x;
    c = Point1.x * Point2.y - Point2.x * Point1.y;
    Normal = Vector2d(a, b);
    NormalModule = Normal.getModule();
    Vector2d normal = 1 / NormalModule * Normal;

    Vector2d offset = 0.5 * Thickness * normal;

    ToDraw[0].position = Point1 - offset;
    ToDraw[1].position = Point2 - offset;
    ToDraw[2].position = Point2 + offset;
    ToDraw[3].position = Point1 + offset;

    for(int i = 0; i < 4; i++)
        ToDraw[i].color = Color;
}


// https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
Vector2d LineSegment::Intersection(const Vector2d& p1, const Vector2d& p2, const LineSegment* line)
{
    Vector2d t1 = line->Point1;
    Vector2d t2 = line->Point2;
    float det =  (p1.x - p2.x)*(t1.y - t2.y) - (p1.y - p2.y)*(t1.x - t2.x);
    if(det == 0)
        return {-1, -1};
    float t = ((p1.x - t1.x)*(t1.y - t2.y) - (p1.y - t1.y)*(t1.x - t2.x)) / det;
    float u = ((p1.x - t1.x)*(p1.y - p2.y) - (p1.y - t1.y)*(p1.x - p2.x)) / det;
    if(t >= 0 && u <= 1 && u >= 0)
        return Vector2d(p1.x + t*(p2.x - p1.x), p1.y + t*(p2.y - p1.y));
    return {-1, -1};
}


int LineSegment::Orientation(const Vector2d& point)
{
    int value = (Point2.y - Point1.y) * (point.x - Point2.x) - \
                (Point2.x - Point1.x) * (point.y - Point2.y);
    if(value == 0)
        return 0;
    return (value > 0) ? 1: 2;
}


float LineSegment::Distance(const Vector2d& point)
{
    return fabs(a * point.x + b * point.y + c) / NormalModule;
}


bool LineSegment::isBelong(const Vector2d& point)
{
    float p = Vector2d::DotProduct(Point1 - point, Point2 - point);
    if(p <= 0)
        return true;
    return false;
}


void LineSegment::Draw(sf::RenderWindow* window)
{
    window->draw(ToDraw, 4, sf::Quads);
}

