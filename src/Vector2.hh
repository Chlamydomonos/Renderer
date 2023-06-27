#pragma once

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
        return rawX / rawZ;
    }
    float y() const
    {
        return rawY / rawZ;
    }

    float operator*(const Vector2& b) const
    {
        return rawX * b.rawX + rawY * b.rawY;
    }

    void asSum(const Vector2& a, const Vector2& b)
    {
        rawX = a.rawX + b.rawX;
        rawY = a.rawY + b.rawY;
    }
    void asDifference(const Vector2& a, const Vector2& b)
    {
        rawX = a.rawX - b.rawX;
        rawY = a.rawY - b.rawY;
    }
    void asProduct(const Matrix2& a, const Vector2& b);
    void asProduct(const Vector2& a, float b)
    {
        rawX = a.rawX * b;
        rawY = a.rawY * b;
    }
    void asQuotient(const Vector2& a, float b)
    {
        rawX = a.rawX / b;
        rawY = a.rawY / b;
    }
};