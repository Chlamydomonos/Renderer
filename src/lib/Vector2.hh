#pragma once

#include <cmath>

/**
 * @brief 2D向量，用齐次坐标表示
 */
class Vector2
{
private:
    float rawX;
    float rawY;
    float rawZ;
    friend class Point2;
    friend class Matrix2;
public:
    Vector2() = default;
    Vector2(float x, float y) : rawX(x), rawY(y), rawZ(0.0f) {}

    float x() const
    {
        return rawX;
    }
    float y() const
    {
        return rawY;
    }

    Vector2 &asSum(const Vector2 &a, const Vector2 &b)
    {
        rawX = a.rawX + b.rawX;
        rawY = a.rawY + b.rawY;
        return *this;
    }
    Vector2 &asDifference(const Vector2 &a, const Vector2 &b)
    {
        rawX = a.rawX - b.rawX;
        rawY = a.rawY - b.rawY;
        return *this;
    }

    /**
     * @note 此函数的参数不能是this
     */
    Vector2 &asProduct(const Matrix2 &a, const Vector2 &b);

    Vector2 &asProduct(const Vector2 &a, float b)
    {
        rawX = a.rawX * b;
        rawY = a.rawY * b;
        return *this;
    }
    Vector2 &asQuotient(const Vector2 &a, float b)
    {
        rawX = a.rawX / b;
        rawY = a.rawY / b;
        return *this;
    }

    Vector2 &copy(const Vector2 &a)
    {
        rawX = a.rawX;
        rawY = a.rawY;
        return *this;
    }

    Vector2 &copy(const Point2 &a);

    Vector2 &normalize()
    {
        float length = sqrt(rawX * rawX + rawY * rawY);
        rawX /= length;
        rawY /= length;
        return *this;
    }

    float operator*(const Vector2 &b) const
    {
        return rawX * b.rawX + rawY * b.rawY;
    }
};