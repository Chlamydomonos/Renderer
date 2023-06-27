#include "Renderer.hh"

#include <wingdi.h>

constexpr COLORREF WHITE = RGB(0xff, 0xff, 0xff);

Renderer Renderer::INSTANCE;

void Renderer::render(PaintDevice canvas)
{
    auto centerX = 500.0f;
    auto centerY = 300.0f;
    Point2 points[200];
    Point2 test1(500.0f, 280.0f);
    for(int i = 0; i < 200; i++)
    {
        auto angle = i * 2 * 3.1415926f / 200;
        Matrix2 matrix;
        matrix.translate(-centerX, -centerY).thenRotate(angle).thenTranslate(centerX, centerY);
        points[i].asProduct(matrix, test1);
    }
    renderPoints(points, 200, canvas);
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