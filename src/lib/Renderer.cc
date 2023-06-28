#include "Renderer.hh"

#include "Model.hh"

#include <wingdi.h>
#include <algorithm>

constexpr Color WHITE = RGB(0xff, 0xff, 0xff);
constexpr Color RED = RGB(0xff, 0x00, 0x00);
constexpr Color GREEN = RGB(0x00, 0xff, 0x00);
constexpr Color BLUE = RGB(0x00, 0x00, 0xff);
constexpr Color YELLOW = RGB(0xff, 0xff, 0x00);
constexpr Color CYAN = RGB(0x00, 0xff, 0xff);
constexpr Color MAGENTA = RGB(0xff, 0x00, 0xff);

constexpr float PI = 3.14159265358979323846f;

Renderer Renderer::INSTANCE;

static Model model(
    {
        Vertex(-1.0f, -1.0f, 9.0f),
        Vertex(1.0f, -1.0f, 9.0f),
        Vertex(1.0f, -1.0f, 11.0f),
        Vertex(-1.0f, -1.0f, 11.0f),
        Vertex(-1.0f, 1.0f, 9.0f),
        Vertex(1.0f, 1.0f, 9.0f),
        Vertex(1.0f, 1.0f, 11.0f),
        Vertex(-1.0f, 1.0f, 11.0f),
    },
    {
        Triangle(0, 1, 2),
        Triangle(0, 2, 3),
        Triangle(4, 6, 5),
        Triangle(4, 7, 6),
        Triangle(0, 4, 5),
        Triangle(0, 5, 1),
        Triangle(1, 5, 6),
        Triangle(1, 6, 2),
        Triangle(2, 6, 7),
        Triangle(2, 7, 3),
        Triangle(3, 7, 4),
        Triangle(3, 4, 0),
    }
);

void Renderer::render(PaintDevice canvas)
{
    Camera camera;
    static float temp;
    if(temp > PI / 4.0f)
    {
        temp = -PI / 4.0f;
    }
    else
    {
        temp += 0.01f;
    }
    camera.setPos(Point3(0.0f, 2.0f, 0.0f));
    camera.setDir(Vector3(sin(temp), sin(-PI / 12.0f), cos(temp)));
    camera.setUp(Vector3(0.0f, cos(-PI / 12.0f), 0.0f));
    model.renderAsWireframe(camera, canvas);
}

void Renderer::render2dPoint(const Point2 &point, PaintDevice canvas, Color color)
{
    SetPixel(canvas, point.x(), WINDOW_HEIGHT - point.y(), color);
}

void Renderer::renderScreenSpacePoint(const Point3 &point, PaintDevice canvas, Color color)
{
    auto x = point.x();
    auto y = WINDOW_HEIGHT - point.y();
    SetPixel(canvas, x, y, color);
}

void Renderer::renderWorldSpacePoint(const Point3 &point, const Camera &camera, PaintDevice canvas, Color color)
{
    static Point3 cameraSpacePoint;
    static Point3 screenSpacePoint;
    cameraSpacePoint.asProduct(camera.getWorldToView(), point);
    screenSpacePoint.asProduct(camera.getViewToScreen(), cameraSpacePoint);

    auto x = screenSpacePoint.x();
    auto y = WINDOW_HEIGHT - screenSpacePoint.y();
    SetPixel(canvas, x, y, color);
}

void Renderer::renderWorldSpaceLine(const Point3 &point0, const Point3 &point1, const Camera &camera, PaintDevice canvas, Color color)
{
    static Point3 cameraSpacePoint;
    static Point3 screenSpacePoint;
    cameraSpacePoint.asProduct(camera.getWorldToView(), point0);
    screenSpacePoint.asProduct(camera.getViewToScreen(), cameraSpacePoint);
    auto x0 = static_cast<int>(screenSpacePoint.x());
    auto y0 = static_cast<int>(WINDOW_HEIGHT - screenSpacePoint.y());
    cameraSpacePoint.asProduct(camera.getWorldToView(), point1);
    screenSpacePoint.asProduct(camera.getViewToScreen(), cameraSpacePoint);
    auto x1 = static_cast<int>(screenSpacePoint.x());
    auto y1 = static_cast<int>(WINDOW_HEIGHT - screenSpacePoint.y());

    auto dx = x1 - x0;
    auto dy = y1 - y0;
    auto steps = max(abs(dx), abs(dy));

    for(auto i = 0; i <= steps; ++i)
    {
        auto x = x0 + i * dx / steps;
        auto y = y0 + i * dy / steps;
        SetPixel(canvas, x, y, color);
    }
}