#include "geometry2.hh"

void Vector2::asProduct(const Matrix2& a, const Vector2& b)
{
    rawX = a.data[0][0] * b.rawX + a.data[0][1] * b.rawY + a.data[0][2] * b.rawZ;
    rawY = a.data[1][0] * b.rawX + a.data[1][1] * b.rawY + a.data[1][2] * b.rawZ;
    rawZ = a.data[2][0] * b.rawX + a.data[2][1] * b.rawY + a.data[2][2] * b.rawZ;
}
