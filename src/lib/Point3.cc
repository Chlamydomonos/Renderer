#include "Point3.hh"

#include "geometry3.hh"

Point3 &Point3::asSum(const Point3 &a, const Vector3 &b)
{
    rawX = a.rawX + b.rawX;
    rawY = a.rawY + b.rawY;
    rawZ = a.rawZ + b.rawZ;
    rawW = a.rawW + b.rawW;
    return *this;
}

Point3 &Point3::asDifference(const Point3 &a, const Vector3 &b)
{
    rawX = a.rawX - b.rawX;
    rawY = a.rawY - b.rawY;
    rawZ = a.rawZ - b.rawZ;
    rawW = a.rawW - b.rawW;
    return *this;
}

Point3 &Point3::asProduct(const Matrix3 &a, const Point3 &b)
{
    rawX = a.data[0][0] * b.rawX + a.data[0][1] * b.rawY + a.data[0][2] * b.rawZ + a.data[0][3];
    rawY = a.data[1][0] * b.rawX + a.data[1][1] * b.rawY + a.data[1][2] * b.rawZ + a.data[1][3];
    rawZ = a.data[2][0] * b.rawX + a.data[2][1] * b.rawY + a.data[2][2] * b.rawZ + a.data[2][3];
    rawW = a.data[3][0] * b.rawX + a.data[3][1] * b.rawY + a.data[3][2] * b.rawZ + a.data[3][3];
    return *this;
}

Point3 &Point3::copy(const Vector3 &a)
{
    rawX = a.rawX;
    rawY = a.rawY;
    rawZ = a.rawZ;
    rawW = 1.0f;
    return *this;
}