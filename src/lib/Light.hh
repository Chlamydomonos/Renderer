#pragma once

#include "geometry3.hh"
#include "VertexColor.hh"

class Light
{
private:
    Vector3 dir;
    float intensity;
    VertexColor color;
public:
    Light() : dir(-1.0f, -1.0f, 0.0f), intensity(1.0f), color(1.0f, 1.0f, 1.0f) {}

    Light(float x, float y, float z, float intensity, const VertexColor &color) : dir(x, y, z), intensity(intensity), color(color)
    {
        dir.normalize();
    }

    const Vector3 &getDir() const
    {
        return dir;
    }

    float getIntensity() const
    {
        return intensity;
    }

    const VertexColor &getColor() const
    {
        return color;
    }
};