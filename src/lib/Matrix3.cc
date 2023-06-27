#include "Matrix3.hh"

#include "geometry3.hh"

Matrix3 &Matrix3::rotate(float theta, const Vector3 &axis)
{
    return rotate(theta, axis.rawX, axis.rawY, axis.rawZ);
}

Matrix3 &Matrix3::thenRotate(float theta, const Vector3 &axis)
{
    return thenRotate(theta, axis.rawX, axis.rawY, axis.rawZ);
}