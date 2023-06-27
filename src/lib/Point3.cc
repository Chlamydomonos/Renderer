#include "Point3.hh"

#include "geometry3.hh"

Point3 &Point3::asProduct(const Matrix3& a, const Point3& b)
{
    rawX = a.data[0][0] * b.rawX + a.data[0][1] * b.rawY + a.data[0][2] * b.rawZ + a.data[0][3];
    rawY = a.data[1][0] * b.rawX + a.data[1][1] * b.rawY + a.data[1][2] * b.rawZ + a.data[1][3];
    rawZ = a.data[2][0] * b.rawX + a.data[2][1] * b.rawY + a.data[2][2] * b.rawZ + a.data[2][3];
    rawW = a.data[3][0] * b.rawX + a.data[3][1] * b.rawY + a.data[3][2] * b.rawZ + a.data[3][3];
    return *this;
}