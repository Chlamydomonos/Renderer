#include "Renderer.hh"

#include "Model.hh"
#include "Controller.hh"

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

static Model simpleTwoTriangles(
    {
        Vertex(-1.0f, -1.0f, 9.0f),
        Vertex(1.0f, -1.0f, 9.0f),
        Vertex(1.0f, 1.0f, 9.0f),
        Vertex(1.0f, -1.0f, 11.0f),
    },
    {
        Triangle(0, 1, 2),
        Triangle(0, 1, 3),
    }
);

static Model simpleTriangle1(
    {
        Vertex(-1.0f, -1.0f, 9.0f),
        Vertex(1.0f, -1.0f, 9.0f),
        Vertex(1.0f, 1.0f, 9.0f),
    },
    {
        Triangle(0, 1, 2)
    }
);

static Model simpleTriangle2(
    {
        Vertex(-1.0f, -1.0f, 9.0f),
        Vertex(1.0f, -1.0f, 9.0f),
        Vertex(1.0f, -1.0f, 11.0f),
    },
    {
        Triangle(0, 1, 2)
    }
);

void Renderer::render(PaintDevice canvas)
{
    resetZBuffer();
    this->canvas = canvas;
    Camera camera;
    static float temp;
    static bool paused;
    if(Controller::INSTANCE.tryGetSpaceSignal())
    {
        paused = !paused;
    }

    if(temp > PI / 4.0f)
    {
        temp = -PI / 4.0f;
    }
    else if(!paused || Controller::INSTANCE.tryGetWSignal())
    {
        temp += 0.01f;
    }
    camera.setPos(Point3(0.0f, 2.0f, 0.0f));
    camera.setDir(Vector3(sin(temp), sin(-PI / 12.0f), cos(temp)));
    camera.setUp(Vector3(0.0f, cos(-PI / 12.0f), 0.0f));
    cube.simpleRender(camera);
    //simpleTwoTriangles.simpleRender(camera);
    //simpleTriangle2.simpleRender(camera, RED, GREEN);
    //simpleTriangle1.simpleRender(camera, WHITE, BLUE);

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
    auto x0 = screenSpacePoint.x();
    auto y0 = WINDOW_HEIGHT - screenSpacePoint.y();
    cameraSpacePoint.asProduct(camera.getWorldToView(), point1);
    screenSpacePoint.asProduct(camera.getViewToScreen(), cameraSpacePoint);
    auto x1 = screenSpacePoint.x();
    auto y1 = WINDOW_HEIGHT - screenSpacePoint.y();

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
    if(z > zBuffer[x][y])
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
    if(z > zBuffer[x][y])
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
        if(z > zBuffer[x][y])
        {
            SetPixel(canvas, x, y, color);
            zBuffer[x][y] = z;
        }
    }
}