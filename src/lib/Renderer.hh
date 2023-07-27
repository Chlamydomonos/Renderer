#pragma once

#include "windows.hh"
#include "geometry2.hh"
#include "geometry3.hh"
#include "Camera.hh"
#include "VertexColor.hh"
#include "FasterBMP.hh"

#include <xutility>

class Renderer
{
private:
    Renderer() {}
    Renderer(const Renderer&) = delete;
    Renderer &operator=(const Renderer&) = delete;
    float zBuffer[WINDOW_WIDTH][WINDOW_HEIGHT]{0.0f};
    FasterBMP bmp;
public:
    static Renderer INSTANCE;
    void resetZBuffer()
    {
        std::fill(&zBuffer[0][0], &zBuffer[0][0] + WINDOW_WIDTH * WINDOW_HEIGHT, 0.0f);
    }
    void init();
    void render(PaintDevice canvas);
    void render2dPoint(const Point2 &point, Color color = 0xffffff);
    void renderScreenSpacePoint(const Point3 &point, Color color = 0xffffff);
    void renderWorldSpacePoint(const Point3 &point, const Camera &camera, Color color = 0xffffff);
    void renderWorldSpaceLine(const Point3 &point0, const Point3 &point1, const Camera &camera, Color color = 0xffffff);
    void renderWorldSpaceLine(const Point3 &point0, const Point3 &point1, const Camera &camera, const VertexColor &color0, const VertexColor &color1);
    void renderScreenSpacePointWithZBuffer(const Point3 &point, Color color = 0xffffff);
    void renderWorldSpacePointWithZBuffer(const Point3 &point, const Camera &camera, Color color = 0xffffff);
    void renderWorldSpaceLineWithZBuffer(const Point3 &point0, const Point3 &point1, const Camera &camera, Color color = 0xffffff);
};