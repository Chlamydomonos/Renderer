#include "Renderer.hh"

#include <wingdi.h>

constexpr COLORREF WHITE = RGB(0xff, 0xff, 0xff);

Renderer Renderer::INSTANCE;

void Renderer::render(PaintDevice canvas)
{
    Point2 point(100.0f, 100.0f);
    renderPoint(point, canvas);
}

void Renderer::renderPoint(Point2 point, PaintDevice canvas)
{
    SetPixel(canvas, point.x(), point.y(), WHITE);
}

void Renderer::renderPoints(Point2* points, int count, PaintDevice canvas)
{
    auto pointsEnd = points + count;
    for (auto point = points; point != pointsEnd; ++point)
    {
        SetPixel(canvas, point->x(), point->y(), WHITE);
    }
}