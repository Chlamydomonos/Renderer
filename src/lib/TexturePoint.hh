#pragma once

class TexturePoint
{
private:
    float x;
    float y;
public:
    TexturePoint() = default;
    TexturePoint(float x, float y) : x(x), y(y) {}
    float getX() const
    {
        return x;
    }
    float getY() const
    {
        return y;
    }
};