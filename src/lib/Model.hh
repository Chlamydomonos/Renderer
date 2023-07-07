#pragma once

#include "Vertex.hh"
#include "Triangle.hh"
#include "Camera.hh"
#include "VertexColor.hh"
#include "Material.hh"
#include "Light.hh"
#include "TexturePoint.hh"
#include "geometry3.hh"

#include <vector>
#include <stdexcept>

class Model
{
private:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
    std::vector<TexturePoint> textures;
    Matrix3 transform;

    void fillTriangle(Point3 &s0, Point3 &s1, Point3 &s2, Color color);
    void fillTriangleWithVertexColor(Point3 &s0, Point3 &s1, Point3 &s2, VertexColor &c0, VertexColor &c1, VertexColor &c2);
    void updateNormals();

    friend class Parser;
public:
    Model() : vertices(), triangles(), textures()
    {
        transform.identity();
        updateNormals();
    }

    Model(const std::vector<Vertex> &vertices, const std::vector<Triangle> &triangles)
    : vertices(vertices), triangles(triangles), textures()
    {
        transform.identity();
        updateNormals();
    }

    Model(const std::vector<Vertex> &vertices, const std::vector<Triangle> &triangles, bool doNotUpdateNormals)
    : vertices(vertices), triangles(triangles), textures()
    {
        transform.identity();
        if (!doNotUpdateNormals)
        {
            updateNormals();
        }
    }

    Model(const std::vector<Vertex> &vertices, const std::vector<Triangle> &triangles, const std::vector<TexturePoint> &textures)
    : vertices(vertices), triangles(triangles), textures(textures)
    {
        transform.identity();
        updateNormals();
    }

    Model(const std::vector<Vertex> &vertices, const std::vector<Triangle> &triangles, const std::vector<TexturePoint> &textures, bool doNotUpdateNormals)
    : vertices(vertices), triangles(triangles), textures(textures)
    {
        transform.identity();
        if (!doNotUpdateNormals)
        {
            updateNormals();
        }
    }

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

    void renderAsWireframe(const Camera &camera, Color color = 0xffffff);
    void renderAswireframeWithoutBackface(const Camera &camera, Color color = 0xffffff);
    void simpleRender(const Camera &camera, Color wireFrameColor = 0xffffff, Color fillColor = 0xff0000);
    void renderWithMaterial(const Camera &camera, const Material &material, const Light &light);
    void applyTransform(const Matrix3 &transform)
    {
        Matrix3 temp;
        temp.asProduct(transform, this->transform);
        this->transform.copy(temp);
    }
};