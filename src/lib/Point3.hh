#pragma once

class Point3
{
private:
    float rawX;
    float rawY;
    float rawZ;
    float rawW;
    friend class Matrix3;
    friend class Vector3;
public:
    Point3() : rawX(), rawY(), rawZ(), rawW(1.0f) {}
    Point3(float x, float y, float z) : rawX(x), rawY(y), rawZ(z), rawW(1.0f) {}

    float x() const
    {
        return rawX / rawW;
    }

    float y() const
    {
        return rawY / rawW;
    }

    float z() const
    {
        return rawZ / rawW;
    }

    void asProduct(const Matrix3& a, const Point3& b);
};