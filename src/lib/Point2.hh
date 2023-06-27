#pragma once

/**
 * @brief 2D点，用齐次坐标表示
 */
class Point2
{
private:
    float rawX;
    float rawY;
    float rawZ;
    friend class Vector2;
    friend class Matrix2;

public:
    Point2() : rawX(), rawY(), rawZ(1.0f) {}
    Point2(float x, float y) : rawX(x), rawY(y), rawZ(1.0f) {}

    float x() const
    {
        return rawX / rawZ;
    }
    float y() const
    {
        return rawY / rawZ;
    }

    Point2 &asSum(const Point2 &a, const Vector2 &b);
    Point2 &asSum(const Point2 &a, const Point2 &b)
    {
        rawX = a.rawX + b.rawX;
        rawY = a.rawY + b.rawY;
        rawZ = a.rawZ + b.rawZ;
        return *this;
    }
    Point2 &asDifference(const Point2 &a, const Vector2 &b);

    /**
     * @note 此函数的参数不能是this
     */
    Point2 &asProduct(const Matrix2 &a, const Point2 &b);

    Point2 &copy(const Point2 &a)
    {
        rawX = a.rawX;
        rawY = a.rawY;
        rawZ = a.rawZ;
        return *this;
    }

    Point2 &copy(const Vector2 &a);
};