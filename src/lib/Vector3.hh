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

    Vector3 &asSum(const Vector3 &a, const Vector3 &b)
    {
        rawX = a.rawX + b.rawX;
        rawY = a.rawY + b.rawY;
        rawZ = a.rawZ + b.rawZ;
        return *this;
    }

    Vector3 &asDifference(const Vector3 &a, const Vector3 &b)
    {
        rawX = a.rawX - b.rawX;
        rawY = a.rawY - b.rawY;
        rawZ = a.rawZ - b.rawZ;
        return *this;
    }

    /**
     * @note 此函数的参数不能是this
     */
    Vector3 &asProduct(const Matrix3 &a, const Vector3 &b);

    /**
     * @note 此函数的参数不能是this
     */
    Vector3 &asProduct(const Vector3 &a, const Vector3 &b)
    {
        rawX = a.rawY * b.rawZ - a.rawZ * b.rawY;
        rawY = a.rawZ * b.rawX - a.rawX * b.rawZ;
        rawZ = a.rawX * b.rawY - a.rawY * b.rawX;
        return *this;
    }

    Vector3 &asProduct(const Vector3 &a, float b)
    {
        rawX = a.rawX * b;
        rawY = a.rawY * b;
        rawZ = a.rawZ * b;
        return *this;
    }

    Vector3 &asQuotient(const Vector3 &a, float b)
    {
        rawX = a.rawX / b;
        rawY = a.rawY / b;
        rawZ = a.rawZ / b;
        return *this;
    }

    Vector3 &copy(const Vector3 &a)
    {
        rawX = a.rawX;
        rawY = a.rawY;
        rawZ = a.rawZ;
        return *this;
    }

    Vector3 &copy(const Point3 &a);

    float operator*(const Vector3 &a) const
    {
        return rawX * a.rawX + rawY * a.rawY + rawZ * a.rawZ;
    }
};