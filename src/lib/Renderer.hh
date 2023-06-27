#pragma once

#include "windows.hh"
#include "geometry2.hh"
#include "geometry3.hh"
#include "Camera.hh"

class Renderer
{
private:
    Renderer() {}
    Renderer(const Renderer&) = delete;
    Renderer &operator=(const Renderer&) = delete;
public:
    static Renderer INSTANCE;
    void render(PaintDevice canvas);
    void render2dPoint(const Point2 &point, PaintDevice canvas);
    void render2dPoints(const Point2 *points, int count, PaintDevice canvas);
    void renderScreenSpacePoint(const Point3 &point, PaintDevice canvas);
    void renderWorldSpacePoint(const Point3 &point, const Camera &camera, PaintDevice canvas);
};