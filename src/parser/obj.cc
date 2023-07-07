#include "obj.hh"

#include "Parser.hh"

extern "C" {

void initParser()
{
    Parser::INSTANCE.init();
}

void addVertex(float x, float y, float z)
{
    Parser::INSTANCE.addVertex(x, y, z);
}

void addNormal(float x, float y, float z)
{
    Parser::INSTANCE.addNormal(x, y, z);
}

void addTexture(float x, float y)
{
    Parser::INSTANCE.addTexture(x, y);
}

void addFace(int v1, int v2, int v3)
{
    Parser::INSTANCE.addFace(v1, v2, v3);
}

void addFaceWithTexture(int v1, int v2, int v3, int t1, int t2, int t3)
{
    Parser::INSTANCE.addFaceWithTexture(v1, v2, v3, t1, t2, t3);
}

void addFaceWithNormal(int v1, int v2, int v3, int n1, int n2, int n3)
{
    Parser::INSTANCE.addFaceWithNormal(v1, v2, v3, n1, n2, n3);
}

void addFaceWithTextureAndNormal(int v1, int v2, int v3, int t1, int t2, int t3, int n1, int n2, int n3)
{
    Parser::INSTANCE.addFace(v1, v2, v3, t1, t2, t3, n1, n2, n3);
}

}