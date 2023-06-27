#include "Renderer.hh"

#include <wingdi.h>

constexpr COLORREF WHITE = RGB(0xff, 0xff, 0xff);

Renderer Renderer::INSTANCE;

static void generateRandomPoints(Point3 *points, int count, float centerX, float centerY, float centerZ, float radius)
{
    for (auto point = points; point != points + count; ++point)
    {
        auto theta = rand() * 2.0f * 3.1415926 / RAND_MAX;
        auto phi = rand() * 2.0f * 3.1415926 / RAND_MAX;
        auto sinTheta = sinf(theta);
        auto cosTheta = cosf(theta);
        auto sinPhi = sinf(phi);
        auto cosPhi = cosf(phi);
        auto x = centerX + radius * sinTheta * cosPhi;
        auto y = centerY + radius * sinTheta * sinPhi;
        auto z = centerZ + radius * cosTheta;
        point->copy(Point3(x, y, z));
    }
}

void Renderer::render(PaintDevice canvas)
{
    Camera camera;
    static float camaraY;
    if(camaraY > 1.0f)
    {
        camaraY = -1.0f;
    }
    else
    {
        camaraY += 0.01f;
    }
    camera.setPos(Point3(-1.0f, camaraY, 0.0f));
    camera.setDir(Vector3(0.0f, 0.0f, 1.0f));
    camera.setUp(Vector3(0.0f, 1.0f, 0.0f));
    auto points = new Point3[600];
    generateRandomPoints(points, 100, 0.0f, 0.0f, 10.0f, 0.1f);
    for(auto point = points; point != points + 100; ++point)
    {
        renderWorldSpacePoint(*point, camera, canvas);
    }
    generateRandomPoints(points + 100, 100, -1.0f, 0.0f, 11.0f, 0.1f);
    for(auto point = points + 100; point != points + 200; ++point)
    {
        renderWorldSpacePoint(*point, camera, canvas);
    }
    generateRandomPoints(points + 200, 100, 1.0f, 0.0f, 11.0f, 0.1f);
    for(auto point = points + 200; point != points + 300; ++point)
    {
        renderWorldSpacePoint(*point, camera, canvas);
    }
    generateRandomPoints(points + 300, 100, 0.0f, 1.0f, 11.0f, 0.1f);
    for(auto point = points + 300; point != points + 400; ++point)
    {
        renderWorldSpacePoint(*point, camera, canvas);
    }
    generateRandomPoints(points + 400, 100, 0.0f, -1.0f, 11.0f, 0.1f);
    for(auto point = points + 400; point != points + 500; ++point)
    {
        renderWorldSpacePoint(*point, camera, canvas);
    }
    generateRandomPoints(points + 500, 100, 0.0f, 0.0f, 12.0f, 0.1f);
    for(auto point = points + 500; point != points + 600; ++point)
    {
        renderWorldSpacePoint(*point, camera, canvas);
    }
    // Point3 point0(0.0f, 0.0f, 10.0f);
    // renderWorldSpacePoint(point0, camera, canvas);
    // Point3 point1(-1.0f, 0.0f, 11.0f);
    // renderWorldSpacePoint(point1, camera, canvas);
    // Point3 point2(1.0f, 0.0f, 11.0f);
    // renderWorldSpacePoint(point2, camera, canvas);
    // Point3 point3(0.0f, 1.0f, 11.0f);
    // renderWorldSpacePoint(point3, camera, canvas);
    // Point3 point4(0.0f, -1.0f, 11.0f);
    // renderWorldSpacePoint(point4, camera, canvas);
    // Point3 point5(0.0f, 0.0f, 12.0f);
    // renderWorldSpacePoint(point5, camera, canvas);
}

void Renderer::render2dPoint(const Point2 &point, PaintDevice canvas)
{
    SetPixel(canvas, point.x(), WINDOW_HEIGHT - point.y(), WHITE);
}

void Renderer::render2dPoints(const Point2 *points, int count, PaintDevice canvas)
{
    auto pointsEnd = points + count;
    for (auto point = points; point != pointsEnd; ++point)
    {
        SetPixel(canvas, point->x(), WINDOW_HEIGHT - point->y(), WHITE);
    }
}

void Renderer::renderScreenSpacePoint(const Point3 &point, PaintDevice canvas)
{
    auto x = point.x();
    auto y = WINDOW_HEIGHT - point.y();
    SetPixel(canvas, x, y, WHITE);
}

void Renderer::renderWorldSpacePoint(const Point3 &point, const Camera &camera, PaintDevice canvas)
{
    static Point3 cameraSpacePoint;
    static Point3 screenSpacePoint;
    cameraSpacePoint.asProduct(camera.getWorldToView(), point);
    screenSpacePoint.asProduct(camera.getViewToScreen(), cameraSpacePoint);

    auto x = screenSpacePoint.x();
    auto y = WINDOW_HEIGHT - screenSpacePoint.y();
    SetPixel(canvas, x, y, WHITE);
}