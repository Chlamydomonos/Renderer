#pragma once

class Point2
{
private:
    float rawX;
    float rawY;
    float rawZ;
public:
    Point2(float x, float y) : rawX(x), rawY(y), rawZ(1.0f) {}

    float x() const
    {
        return rawX / rawZ;
    }
    float y() const
    {
        return rawY / rawZ;
    }
};