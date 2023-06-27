#include "Vector2.hh"

#include "geometry2.hh"

Vector2 &Vector2::asProduct(const Matrix2 &a, const Vector2 &b)
{
    rawX = a.data[0][0] * b.rawX + a.data[0][1] * b.rawY;
    rawY = a.data[1][0] * b.rawX + a.data[1][1] * b.rawY;
    return *this;
}

Vector2 &Vector2::copy(const Point2 &a)
{
    rawX = a.rawX / a.rawZ;
    rawY = a.rawY / a.rawZ;
    rawZ = 0.0f;
    return *this;
}