#include "Vector3.hh"

#include "geometry3.hh"

Vector3 &Vector3::asDifference(const Point3 &a, const Point3 &b)
{
    rawX = a.x() - b.x();
    rawY = a.y() - b.y();
    rawZ = a.z() - b.z();
    rawW = 0;
    return *this;
}

Vector3 &Vector3::asProduct(const Matrix3 &a, const Vector3 &b)
{
    rawX = a.data[0][0] * b.rawX + a.data[0][1] * b.rawY + a.data[0][2] * b.rawZ;
    rawY = a.data[1][0] * b.rawX + a.data[1][1] * b.rawY + a.data[1][2] * b.rawZ;
    rawZ = a.data[2][0] * b.rawX + a.data[2][1] * b.rawY + a.data[2][2] * b.rawZ;
    return *this;
}

Vector3 &Vector3::copy(const Point3 &a)
{
    rawX = a.rawX / a.rawW;
    rawY = a.rawY / a.rawW;
    rawZ = a.rawZ / a.rawW;
    return *this;
}