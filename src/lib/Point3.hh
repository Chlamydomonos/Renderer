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

    Point3 &asSum(const Point3 &a, const Point3 &b)
    {
        rawX = a.rawX + b.rawX;
        rawY = a.rawY + b.rawY;
        rawZ = a.rawZ + b.rawZ;
        rawW = a.rawW + b.rawW;
        return *this;
    }

    Point3 &asSum(const Point3 &a, const Vector3 &b);

    Point3 &asDifference(const Point3 &a, const Vector3 &b);

    /**
     * @note 此函数的参数不能是this
     */
    Point3 &asProduct(const Matrix3 &a, const Point3 &b);

    Point3 &asProduct(const Point3 &a, const Point3 &b)
    {
        auto ax = a.x();
        auto ay = a.y();
        auto az = a.z();
        auto bx = b.x();
        auto by = b.y();
        auto bz = b.z();
        rawX = az * by - ay * bz;
        rawY = az * bx - ax * bz;
        rawZ = ay * bx - ax * by;
        rawW = 1.0f;
    }

    Point3 &copy(const Point3 &a)
    {
        rawX = a.rawX;
        rawY = a.rawY;
        rawZ = a.rawZ;
        rawW = a.rawW;
        return *this;
    }

    Point3 &copy(const Vector3 &a);

    float operator*(const Point3 &a) const
    {
        return (rawX * a.rawX + rawY * a.rawY + rawZ * a.rawZ) / (rawW * a.rawW);
    }
};