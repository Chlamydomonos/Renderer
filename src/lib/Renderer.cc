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

static Model cube(
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
    this->canvas = canvas;
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
        renderWorldSpacePoint(*point, camera, WHITE);
    }
    generateRandomPoints(points + 100, 100, -1.0f, 0.0f, 11.0f, 0.1f);
    for(auto point = points + 100; point != points + 200; ++point)
    {
        renderWorldSpacePoint(*point, camera, RED);
    }
    generateRandomPoints(points + 200, 100, 1.0f, 0.0f, 11.0f, 0.1f);
    for(auto point = points + 200; point != points + 300; ++point)
    {
        renderWorldSpacePoint(*point, camera, GREEN);
    }
    generateRandomPoints(points + 300, 100, 0.0f, 1.0f, 11.0f, 0.1f);
    for(auto point = points + 300; point != points + 400; ++point)
    {
        renderWorldSpacePoint(*point, camera, BLUE);
    }
    generateRandomPoints(points + 400, 100, 0.0f, -1.0f, 11.0f, 0.1f);
    for(auto point = points + 400; point != points + 500; ++point)
    {
        renderWorldSpacePoint(*point, camera, YELLOW);
    }
    generateRandomPoints(points + 500, 100, 0.0f, 0.0f, 12.0f, 0.1f);
    for(auto point = points + 500; point != points + 600; ++point)
    {
        renderWorldSpacePoint(*point, camera, CYAN);
    }
    // Point3 point0(0.0f, 0.0f, 10.0f);
    // renderWorldSpacePoint(point0, camera);
    // Point3 point1(-1.0f, 0.0f, 11.0f);
    // renderWorldSpacePoint(point1, camera);
    // Point3 point2(1.0f, 0.0f, 11.0f);
    // renderWorldSpacePoint(point2, camera);
    // Point3 point3(0.0f, 1.0f, 11.0f);
    // renderWorldSpacePoint(point3, camera);
    // Point3 point4(0.0f, -1.0f, 11.0f);
    // renderWorldSpacePoint(point4, camera);
    // Point3 point5(0.0f, 0.0f, 12.0f);
    // renderWorldSpacePoint(point5, camera);
}

void Renderer::render2dPoint(const Point2 &point, Color color)
{
    SetPixel(canvas, point.x(), WINDOW_HEIGHT - point.y(), color);
}

void Renderer::renderScreenSpacePoint(const Point3 &point, Color color)
{
    auto x = point.x();
    auto y = WINDOW_HEIGHT - point.y();
    SetPixel(canvas, x, y, color);
}

void Renderer::renderWorldSpacePoint(const Point3 &point, const Camera &camera, Color color)
{
    static Point3 cameraSpacePoint;
    static Point3 screenSpacePoint;
    cameraSpacePoint.asProduct(camera.getWorldToView(), point);
    screenSpacePoint.asProduct(camera.getViewToScreen(), cameraSpacePoint);

    auto x = screenSpacePoint.x();
    auto y = WINDOW_HEIGHT - screenSpacePoint.y();
    SetPixel(canvas, x, y, color);
}

void Renderer::renderWorldSpaceLine(const Point3 &point0, const Point3 &point1, const Camera &camera, Color color)
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

void Renderer::renderScreenSpacePointWithZBuffer(const Point3 &point, Color color)
{
    auto x = static_cast<int>(point.x());
    auto y = static_cast<int>(WINDOW_HEIGHT - point.y());
    if(x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
    {
        return;
    }

    auto z = point.z();
    if(z < zBuffer[x][y])
    {
        SetPixel(canvas, x, y, color);
        zBuffer[x][y] = z;
    }
}

void Renderer::renderWorldSpacePointWithZBuffer(const Point3 &point, const Camera &camera, Color color)
{
    static Point3 cameraSpacePoint;
    static Point3 screenSpacePoint;
    cameraSpacePoint.asProduct(camera.getWorldToView(), point);
    screenSpacePoint.asProduct(camera.getViewToScreen(), cameraSpacePoint);

    auto x = static_cast<int>(screenSpacePoint.x());
    auto y = static_cast<int>(WINDOW_HEIGHT - screenSpacePoint.y());
    if(x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
    {
        return;
    }
    auto z = screenSpacePoint.z();
    if(z < zBuffer[x][y])
    {
        SetPixel(canvas, x, y, color);
        zBuffer[x][y] = z;
    }
}

void Renderer::renderWorldSpaceLineWithZBuffer(const Point3 &point0, const Point3 &point1, const Camera &camera, Color color)
{
    static Point3 cameraSpacePoint;
    static Point3 screenSpacePoint;
    cameraSpacePoint.asProduct(camera.getWorldToView(), point0);
    screenSpacePoint.asProduct(camera.getViewToScreen(), cameraSpacePoint);
    auto x0 = static_cast<int>(screenSpacePoint.x());
    auto y0 = static_cast<int>(WINDOW_HEIGHT - screenSpacePoint.y());
    auto z0 = screenSpacePoint.z();
    cameraSpacePoint.asProduct(camera.getWorldToView(), point1);
    screenSpacePoint.asProduct(camera.getViewToScreen(), cameraSpacePoint);
    auto x1 = static_cast<int>(screenSpacePoint.x());
    auto y1 = static_cast<int>(WINDOW_HEIGHT - screenSpacePoint.y());
    auto z1 = screenSpacePoint.z();

    auto dx = x1 - x0;
    auto dy = y1 - y0;
    auto dz = z1 - z0;
    auto steps = max(abs(dx), abs(dy));

    for(auto i = 0; i <= steps; ++i)
    {
        auto x = x0 + i * dx / steps;
        auto y = y0 + i * dy / steps;
        if(x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        {
            continue;
        }
        auto z = z0 + i * dz / steps;
        if(z < zBuffer[x][y])
        {
            SetPixel(canvas, x, y, color);
            zBuffer[x][y] = z;
        }
    }
}