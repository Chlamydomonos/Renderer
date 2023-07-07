#include "Parser.hh"

#include "obj.hh"

Parser Parser::INSTANCE{};

void Parser::init()
{
    vertices.clear();
    triangles.clear();
    textures.clear();
    normals.clear();
}

void Parser::addVertex(float x, float y, float z)
{
    vertices.push_back(Vertex(x, y, z));
}

void Parser::addNormal(float x, float y, float z)
{
    normals.push_back(Vector3(x, y, z));
}

void Parser::addTexture(float x, float y)
{
    textures.push_back(TexturePoint(x, y));
}

void Parser::addFace(int v1, int v2, int v3)
{
    triangles.push_back(Triangle(v1 - 1, v2 - 1, v3 - 1));
}

void Parser::addFaceWithTexture(int v1, int v2, int v3, int t1, int t2, int t3)
{
    triangles.push_back(Triangle(v1 - 1, v2 - 1, v3 - 1, t1 - 1, t2 - 1, t3 - 1));
}

void Parser::addFaceWithNormal(int v1, int v2, int v3, int n1, int n2, int n3)
{
    triangles.push_back(Triangle(v1 - 1, v2 - 1, v3 - 1));
    vertices[v1 - 1].normal.asSum(vertices[v1 - 1].normal, normals[n1 - 1]);
    vertices[v2 - 1].normal.asSum(vertices[v2 - 1].normal, normals[n2 - 1]);
    vertices[v3 - 1].normal.asSum(vertices[v3 - 1].normal, normals[n3 - 1]);
}

void Parser::addFace(int v1, int v2, int v3, int t1, int t2, int t3, int n1, int n2, int n3)
{
    triangles.push_back(Triangle(v1 - 1, v2 - 1, v3 - 1, t1 - 1, t2 - 1, t3 - 1));
    vertices[v1 - 1].normal.asSum(vertices[v1 - 1].normal, normals[n1 - 1]);
    vertices[v2 - 1].normal.asSum(vertices[v2 - 1].normal, normals[n2 - 1]);
    vertices[v3 - 1].normal.asSum(vertices[v3 - 1].normal, normals[n3 - 1]);
}

std::unique_ptr<Model> Parser::parse(const char *filename)
{
    parseFile(filename);
    auto model = std::make_unique<Model>(vertices, triangles, textures, true);
    if(normals.empty())
    {
        model->updateNormals();
    }
    else
    {
        for (auto &vertex : model->vertices)
        {
            vertex.normal.normalize();
        }
    }
    return model;
}