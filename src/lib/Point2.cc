#include "Point2.hh"

#include "geometry2.hh"

Point2 &Point2::asSum(const Point2 &a, const Vector2 &b)
{
    rawX = a.rawX + b.rawX;
    rawY = a.rawY + b.rawY;
    return *this;
}

Point2 &Point2::asDifference(const Point2 &a, const Vector2 &b)
{
    rawX = a.rawX - b.rawX;
    rawY = a.rawY - b.rawY;
    return *this;
}

Point2 &Point2::asProduct(const Matrix2 &a, const Point2 &b)
{
    rawX = a.data[0][0] * b.rawX + a.data[0][1] * b.rawY + a.data[0][2] * b.rawZ;
    rawY = a.data[1][0] * b.rawX + a.data[1][1] * b.rawY + a.data[1][2] * b.rawZ;
    rawZ = a.data[2][0] * b.rawX + a.data[2][1] * b.rawY + a.data[2][2] * b.rawZ;
    return *this;
}

Point2 &Point2::copy(const Vector2 &a)
{
    rawX = a.rawX;
    rawY = a.rawY;
    rawZ = 1.0f;
    return *this;
}