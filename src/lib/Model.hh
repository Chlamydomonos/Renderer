#pragma once

#include "Vertex.hh"
#include "Triangle.hh"
#include "Camera.hh"

#include <vector>
#include <stdexcept>

class Model
{
private:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
public:
    Model() = default;
    Model(const std::vector<Vertex> &vertices, const std::vector<Triangle> &triangles) : vertices(vertices), triangles(triangles) {}

    std::vector<Vertex> &getVertices()
    {
        return vertices;
    }

    const std::vector<Vertex> &getVertices() const
    {
        return vertices;
    }

    std::vector<Triangle> &getTriangles()
    {
        return triangles;
    }

    const std::vector<Triangle> &getTriangles() const
    {
        return triangles;
    }

    Vertex &getVertex(const Triangle &triangle, int index)
    {
        switch (index)
        {
        case 0:
            return vertices[triangle.getV0()];
        case 1:
            return vertices[triangle.getV1()];
        case 2:
            return vertices[triangle.getV2()];
        default:
            throw std::runtime_error("Invalid vertex index");
        }
    }

    const Vertex &getVertex(const Triangle &triangle, int index) const
    {
        switch (index)
        {
        case 0:
            return vertices[triangle.getV0()];
        case 1:
            return vertices[triangle.getV1()];
        case 2:
            return vertices[triangle.getV2()];
        default:
            throw std::runtime_error("Invalid vertex index");
        }
    }

    void renderAsWireframe(const Camera &camera, PaintDevice canvas, Color color = 0xffffff);
};