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
public:
    Vector2(float x, float y) : rawX(x), rawY(y), rawZ(0.0f) {}

    float x() const
    {
        return rawX / rawZ;
    }
    float y() const
    {
        return rawY / rawZ;
    }
};