#pragma once

#include "Vertex.hh"
#include "Triangle.hh"

#include <vector>

class Model
{
private:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
public:
    Model() = default;

    std::vector<Vertex> &getVertices()
    {
        return vertices;
    }
    std::vector<Triangle> &getTriangles()
    {
        return triangles;
    }
};