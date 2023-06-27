#pragma once

class Vector3
{
private:
    float rawX;
    float rawY;
    float rawZ;
    float rawW;
    friend class Point3;
    friend class Matrix3;
public:
    Vector3() : rawX(), rawY(), rawZ(), rawW(0.0f) {}
    Vector3(float x, float y, float z) : rawX(x), rawY(y), rawZ(z), rawW(0.0f) {}

    float x() const
    {
        return rawX;
    }

    float y() const
    {
        return rawY;
    }

    float z() const
    {
        return rawZ;
    }
};