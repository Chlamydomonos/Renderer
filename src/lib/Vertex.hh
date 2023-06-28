#pragma once

#include "geometry3.hh"

class Vertex
{
private:
    Point3 pos;
public:
    Vertex() = default;
    Vertex(float x, float y, float z) : pos(x, y, z) {}
    Point3 &getPos()
    {
        return pos;
    }

    const Point3 &getPos() const
    {
        return pos;
    }
};