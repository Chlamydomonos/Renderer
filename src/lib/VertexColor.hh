#pragma once

#include "windows.hh"

class VertexColor
{
private:
    float r;
    float g;
    float b;
public:
    VertexColor() = default;
    VertexColor(float r, float g, float b) : r(r), g(g), b(b) {}
    float getR() const
    {
        return r;
    }

    float getG() const
    {
        return g;
    }

    float getB() const
    {
        return b;
    }

    Color toColor() const
    {
        return RGB(min(r, 1.0f) * 255, min(g, 1.0f)  * 255, min(b, 1.0f)  * 255);
    }

    void fromColor(Color color)
    {
        r = GetRValue(color) / 255.0f;
        g = GetGValue(color) / 255.0f;
        b = GetBValue(color) / 255.0f;
    }

    VertexColor &asSum(const VertexColor &a, const VertexColor &b)
    {
        this->r = a.r + b.r;
        this->g = a.g + b.g;
        this->b = a.b + b.b;
        return *this;
    }

    VertexColor &asProduct(const VertexColor &a, float b)
    {
        this->r = a.r * b;
        this->g = a.g * b;
        this->b = a.b * b;
        return *this;
    }

    VertexColor &asProduct(const VertexColor &a, const VertexColor &b)
    {
        this->r = a.r * b.r;
        this->g = a.g * b.g;
        this->b = a.b * b.b;
        return *this;
    }

    VertexColor &copy(const VertexColor &other)
    {
        this->r = other.r;
        this->g = other.g;
        this->b = other.b;
        return *this;
    }

    VertexColor &restrictColor()
    {
        r = min(r, 1.0f);
        g = min(g, 1.0f);
        b = min(b, 1.0f);
        return *this;
    }
};