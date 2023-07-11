#include "Renderer.hh"

#include "Model.hh"
#include "Controller.hh"
#include "Parser.hh"
#include "FPController.hh"

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

static std::unique_ptr<Model> cube;
static std::unique_ptr<Model> importedModel;
static Camera camera;
static Material material;
static Light light;
static FPController controller;
static std::unique_ptr<TexturedMaterial> texturedMaterial;
static std::unique_ptr<TexturedMaterial> cubeMaterial;
static enum Mode
{
    CUBE_WIREFRAME = 0,
    CUBE_SIMPLE,
    CUBE_FLAT,
    CUBE_GOURAUD,
    CUBE_PHONG,
    BUNNY_WIREFRAME,
    BUNNY_SIMPLE,
    BUNNY_FLAT,
    BUNNY_GOURAUD,
    BUNNY_PHONG,
} mode;

void Renderer::init()
{
    importedModel = Parser::INSTANCE.parse("D:/bunny.obj");
    cube = Parser::INSTANCE.parse("D:/cube.obj");
    Matrix3 transform;
    transform.scale(0.1f, 0.1f, 0.1f).thenTranslate(0.0f, 0.0f, 20.0f);
    importedModel->applyTransform(transform);
    Matrix3 cubeTransform;
    cubeTransform.translate(0.0f, 0.0f, 10.0f);
    cube->applyTransform(cubeTransform);

    auto bitmap = (Bitmap)LoadImage(NULL, "D:/texture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    texturedMaterial = std::make_unique<TexturedMaterial>(bitmap);
    bitmap = (Bitmap)LoadImage(NULL, "D:/cube.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    cubeMaterial = std::make_unique<TexturedMaterial>(bitmap);
}

void Renderer::render(PaintDevice canvas)
{
    resetZBuffer();
    this->canvas = canvas;

    auto currentModel = (int)mode / 5 ? importedModel.get() : cube.get();

    if(Controller::INSTANCE.isWDown())
    {
        controller.moveForward(0.05f);
    }
    if(Controller::INSTANCE.isADown())
    {
        controller.moveRight(-0.05f);
    }
    if(Controller::INSTANCE.isSDown())
    {
        controller.moveForward(-0.05f);
    }
    if(Controller::INSTANCE.isDDown())
    {
        controller.moveRight(0.05f);
    }
    if(Controller::INSTANCE.isSpaceDown())
    {
        controller.moveUp(0.05f);
    }
    if(Controller::INSTANCE.isShiftDown())
    {
        controller.moveUp(-0.05f);
    }
    if(Controller::INSTANCE.isLeftDown())
    {
        controller.rotateYaw(-0.01f);
    }
    if(Controller::INSTANCE.isRightDown())
    {
        controller.rotateYaw(0.01f);
    }
    if(Controller::INSTANCE.isUpDown())
    {
        controller.rotatePitch(0.01f);
    }
    if(Controller::INSTANCE.isDownDown())
    {
        controller.rotatePitch(-0.01f);
    }
    if(Controller::INSTANCE.isIDown())
    {
        currentModel->translate(0.0f, 0.1f, 0.0f);
    }
    if(Controller::INSTANCE.isKDown())
    {
        currentModel->translate(0.0f, -0.1f, 0.0f);
    }
    if(Controller::INSTANCE.isJDown())
    {
        currentModel->translate(-0.1f, 0.0f, 0.0f);
    }
    if(Controller::INSTANCE.isLDown())
    {
        currentModel->translate(0.1f, 0.0f, 0.0f);
    }
    if(Controller::INSTANCE.isQDown())
    {
        currentModel->rotateY(-0.1f);
    }
    if(Controller::INSTANCE.isEDown())
    {
        currentModel->rotateY(0.1f);
    }

    for(int i = 0; i < 10; i++)
    {
        if(Controller::INSTANCE.tryGetSignal(i))
        {
            mode = (Mode)i;
        }
    }

    camera.fromFPController(controller);

    switch(mode)
    {
    case CUBE_WIREFRAME:
        cube->renderAsWireframe(camera);
        break;
    case CUBE_SIMPLE:
        cube->renderAswireframeWithoutBackface(camera);
        break;
    case CUBE_FLAT:
        cube->simpleRender(camera);
        break;
    case CUBE_GOURAUD:
        cube->renderWithMaterial(camera, material, light);
        break;
    case CUBE_PHONG:
        cube->renderWithTexture(camera, *cubeMaterial, light);
        break;
    case BUNNY_WIREFRAME:
        importedModel->renderAsWireframe(camera);
        break;
    case BUNNY_SIMPLE:
        importedModel->renderAswireframeWithoutBackface(camera);
        break;
    case BUNNY_FLAT:
        importedModel->simpleRender(camera);
        break;
    case BUNNY_GOURAUD:
        importedModel->renderWithMaterial(camera, material, light);
        break;
    case BUNNY_PHONG:
        importedModel->renderWithTexture(camera, *texturedMaterial, light);
        break;
    }
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

void Renderer::renderWorldSpaceLine(const Point3 &point0, const Point3 &point1, const Camera &camera, const VertexColor &color0, const VertexColor &color1)
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
        auto t = static_cast<float>(i) / steps;
        VertexColor c0, c1;
        c0.asProduct(color0, 1.0f - t);
        c1.asProduct(color1, t);
        c0.asSum(c0, c1);
        SetPixel(canvas, x, y, c0.toColor());
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
    screenSpacePoint.asProduct(camera.getViewToScreen(), cameraSpacePoint).moveToPixelCenter();
    auto x0 = static_cast<int>(screenSpacePoint.x());
    auto y0 = static_cast<int>(WINDOW_HEIGHT - screenSpacePoint.y());
    auto z0 = screenSpacePoint.z();
    cameraSpacePoint.asProduct(camera.getWorldToView(), point1);
    screenSpacePoint.asProduct(camera.getViewToScreen(), cameraSpacePoint).moveToPixelCenter();
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