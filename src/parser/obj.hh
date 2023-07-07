#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void parseFile(const char *filename);
void initParser();
void addVertex(float x, float y, float z);
void addNormal(float x, float y, float z);
void addTexture(float x, float y);
void addFace(int v1, int v2, int v3);
void addFaceWithTexture(int v1, int v2, int v3, int t1, int t2, int t3);
void addFaceWithNormal(int v1, int v2, int v3, int n1, int n2, int n3);
void addFaceWithTextureAndNormal(int v1, int v2, int v3, int t1, int t2, int t3, int n1, int n2, int n3);

#ifdef __cplusplus
}
#endif