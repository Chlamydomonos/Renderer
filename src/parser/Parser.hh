#pragma once

#include "Model.hh"

#include <memory>

class Parser
{
private:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
    std::vector<TexturePoint> textures;
    std::vector<Vector3> normals;
public:
    static Parser INSTANCE;
    Parser() = default;
    void init();
    std::unique_ptr<Model> parse(const char *filename);
    void addVertex(float x, float y, float z);
    void addNormal(float x, float y, float z);
    void addTexture(float x, float y);
    void addFace(int v1, int v2, int v3);
    void addFaceWithTexture(int v1, int v2, int v3, int t1, int t2, int t3);
    void addFaceWithNormal(int v1, int v2, int v3, int n1, int n2, int n3);
    void addFace(int v1, int v2, int v3, int t1, int t2, int t3, int n1, int n2, int n3);
};