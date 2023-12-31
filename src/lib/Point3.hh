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

    float w() const
    {
        return rawW;
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

    Point3 &moveToPixelCenter()
    {
        rawX = static_cast<int>(x()) + 0.5f;
        rawY = static_cast<int>(y()) + 0.5f;
        rawZ = z();
        rawW = 1.0f;
        return *this;
    }

    float operator*(const Point3 &a) const
    {
        return (rawX * a.rawX + rawY * a.rawY + rawZ * a.rawZ) / (rawW * a.rawW);
    }

    Point3 &asBarycentric(const Point3 &a, const Point3 &b, const Point3 &c, const Point3 &self)
    {
        auto gamma = (a.y() - b.y()) * self.x() + (b.x() - a.x()) * self.y() + a.x() * b.y() - b.x() * a.y();
        gamma /= (a.y() - b.y()) * c.x() + (b.x() - a.x()) * c.y() + a.x() * b.y() - b.x() * a.y();

        auto beta = (a.y() - c.y()) * self.x() + (c.x() - a.x()) * self.y() + a.x() * c.y() - c.x() * a.y();
        beta /= (a.y() - c.y()) * b.x() + (c.x() - a.x()) * b.y() + a.x() * c.y() - c.x() * a.y();

        rawX = 1.0f - beta - gamma;
        rawY = beta;
        rawZ = gamma;
        rawW = 1.0f;
        return *this;
    }
};