#pragma once

#include "windows.hh"
#include "geometry2.hh"

class Renderer
{
private:
    Renderer() {}
    Renderer(const Renderer&) = delete;
    Renderer &operator=(const Renderer&) = delete;
public:
    static Renderer INSTANCE;
    void render(PaintDevice canvas);
    void renderPoint(Point2 point, PaintDevice canvas);
    void renderPoints(Point2* points, int count, PaintDevice canvas);
};