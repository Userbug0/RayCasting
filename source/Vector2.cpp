#include "Vector2.h"


Vector2 Vector2::Reflect(const Vector2& ToReflect, const Vector2& v)
{
    Vector2 res = ToReflect;
    float m = v.getModule();
    float temp = Vector2::DotProduct(res, v) / (m * m);
    res -= 2 * temp * v;
    return res;
}

Vector2& Vector2::rotate(float angle, Vector2 point)
{
    float sn = sin(angle);
    float cs = cos(angle);
    Vector2 temp(x, y);
    x = cs * (temp.x - point.x) - sn * (temp.y - point.y) + point.x;
    y = sn * (temp.x - point.x) + cs * (temp.y - point.y) + point.y;
    return *this;

}

Vector2& Vector2::operator+=(const Vector2& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2& Vector2::normalize()
{
    float m = getModule();
    x /= m, y /= m;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
    os << "Vector2d(" << v.x << ", " << v.y << ')' << std::endl;
    return os;
}
