#include "Model.hh"

#include "Renderer.hh"
#include "windows.hh"
#include "BarycentricPoint.hh"

#include <fstream>

static inline void fillType1(const Point3 &s0, const Point3 &s1, const Point3 &s2, Color color)
{
    if(static_cast<int>(s2.y()) == static_cast<int>(s1.y()))
    {
        return;
    }

    auto yStart = static_cast<int>(s0.y());
    auto yEnd = static_cast<int>(s2.y());
    auto dx0 = s2.x() - s0.x();
    auto dy0 = s2.y() - s0.y();
    auto dx1 = s2.x() - s1.x();
    auto dy1 = s2.y() - s1.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y < yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s1.y()) * dx1 / dy1 + s1.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x < xEnd; x++)
        {
            Point3 point(x, y, 0);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());

            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(Point3(x, y, z), color);
        }
    }
}

static inline void fillType2(const Point3 &s0, const Point3 &s1, const Point3 &s2, Color color)
{
    auto yStart = static_cast<int>(s0.y());
    auto yEnd = static_cast<int>(s2.y());
    auto dx0 = s1.x() - s0.x();
    auto dy0 = s1.y() - s0.y();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y < yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x < xEnd; x++)
        {
            Point3 point(x, y, 0);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());

            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(Point3(x, y, z), color);
        }
    }
}

static inline void fillType3LowerPart(const Point3 &s0, const Point3 &s1, const Point3 &s2, Color color)
{
    auto yStart = static_cast<int>(s0.y());
    auto yEnd = static_cast<int>(s1.y());
    auto dx0 = s1.x() - s0.x();
    auto dy0 = s1.y() - s0.y();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x < xEnd; x++)
        {
            Point3 point(x, y, 0);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(Point3(x, y, z), color);
        }
    }
}

static inline void fillType3UpperPart(const Point3 &s0, const Point3 &s1, const Point3 &s2, Color color)
{
    auto yStart = static_cast<int>(s1.y());
    auto yEnd = static_cast<int>(s2.y());
    auto dx0 = s2.x() - s1.x();
    auto dy0 = s2.y() - s1.y();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y < yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s1.y()) * dx0 / dy0 + s1.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x < xEnd; x++)
        {
            Point3 point(x, y, 0);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(Point3(x, y, z), color);
        }
    }
}

static inline void fillVType1(const Point3 &s0, const Point3 &s1, const Point3 &s2, VertexColor &c0, VertexColor &c1, VertexColor &c2)
{
    if(static_cast<int>(s2.y()) == static_cast<int>(s1.y()))
    {
        return;
    }

    auto yStart = static_cast<int>(s0.y());
    auto yEnd = static_cast<int>(s2.y());
    auto dx0 = s2.x() - s0.x();
    auto dy0 = s2.y() - s0.y();
    auto dx1 = s2.x() - s1.x();
    auto dy1 = s2.y() - s1.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s1.y()) * dx1 / dy1 + s1.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            Point3 point(x + 0.5f, y + 0.5f, 0.0f);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());
            VertexColor color(
                barycentric.interpolate(c0.getR(), c1.getR(), c2.getR()),
                barycentric.interpolate(c0.getG(), c1.getG(), c2.getG()),
                barycentric.interpolate(c0.getB(), c1.getB(), c2.getB())
            );
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(Point3(x, y, z), color.toColor());
        }
    }
}

static inline void fillVType2(const Point3 &s0, const Point3 &s1, const Point3 &s2, VertexColor &c0, VertexColor &c1, VertexColor &c2)
{
    auto yStart = static_cast<int>(s0.y());
    auto yEnd = static_cast<int>(s2.y());
    auto dx0 = s1.x() - s0.x();
    auto dy0 = s1.y() - s0.y();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            Point3 point(x + 0.5f, y + 0.5f, 0.0f);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());
            VertexColor color(
                barycentric.interpolate(c0.getR(), c1.getR(), c2.getR()),
                barycentric.interpolate(c0.getG(), c1.getG(), c2.getG()),
                barycentric.interpolate(c0.getB(), c1.getB(), c2.getB())
            );
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(Point3(x, y, z), color.toColor());
        }
    }
}

static inline void fillVType3LowerPart(const Point3 &s0, const Point3 &s1, const Point3 &s2, VertexColor &c0, VertexColor &c1, VertexColor &c2)
{
    auto yStart = static_cast<int>(s0.y());
    auto yEnd = static_cast<int>(s1.y());
    auto dx0 = s1.x() - s0.x();
    auto dy0 = s1.y() - s0.y();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            Point3 point(x + 0.5f, y + 0.5f, 0.0f);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());
            VertexColor color(
                barycentric.interpolate(c0.getR(), c1.getR(), c2.getR()),
                barycentric.interpolate(c0.getG(), c1.getG(), c2.getG()),
                barycentric.interpolate(c0.getB(), c1.getB(), c2.getB())
            );
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(Point3(x, y, z), color.toColor());
        }
    }
}

static inline void fillVType3UpperPart(const Point3 &s0, const Point3 &s1, const Point3 &s2, VertexColor &c0, VertexColor &c1, VertexColor &c2)
{
    auto yStart = static_cast<int>(s1.y());
    auto yEnd = static_cast<int>(s2.y());
    auto dx0 = s2.x() - s1.x();
    auto dy0 = s2.y() - s1.y();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s1.y()) * dx0 / dy0 + s1.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            Point3 point(x + 0.5f, y + 0.5f, 0.0f);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());
            VertexColor color(
                barycentric.interpolate(c0.getR(), c1.getR(), c2.getR()),
                barycentric.interpolate(c0.getG(), c1.getG(), c2.getG()),
                barycentric.interpolate(c0.getB(), c1.getB(), c2.getB())
            );
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(Point3(x, y, z), color.toColor());
        }
    }
}

static inline void fillTType1(const Point3 &w0, const Point3 &w1, const Point3 &w2, const Point3 &s0, const Point3 &s1, const Point3 &s2, const TexturePoint &t1, const TexturePoint &t2, const TexturePoint &t3, const Vector3 &n1, const Vector3 &n2, const Vector3 &n3, const TexturedMaterial &material, const Light &light, const Camera &camera)
{
    if(static_cast<int>(s2.y()) == static_cast<int>(s1.y()))
    {
        return;
    }

    auto yStart = static_cast<int>(s0.y());
    auto yEnd = static_cast<int>(s2.y());
    auto dx0 = s2.x() - s0.x();
    auto dy0 = s2.y() - s0.y();
    auto dx1 = s2.x() - s1.x();
    auto dy1 = s2.y() - s1.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s1.y()) * dx1 / dy1 + s1.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            Point3 point(x + 0.5f, y + 0.5f, 0.0f);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());
            Point3 worldPoint(
                barycentric.interpolate(w0.x(), w1.x(), w2.x()),
                barycentric.interpolate(w0.y(), w1.y(), w2.y()),
                barycentric.interpolate(w0.z(), w1.z(), w2.z())
            );
            Point3 screenPoint(x, y, z);
            Vector3 normal(
                barycentric.interpolate(n1.x(), n2.x(), n3.x()),
                barycentric.interpolate(n1.y(), n2.y(), n3.y()),
                barycentric.interpolate(n1.z(), n2.z(), n3.z())
            );
            TexturePoint uv(
                barycentric.interpolate(t1.getX(), t2.getX(), t3.getX()),
                barycentric.interpolate(t1.getY(), t2.getY(), t3.getY())
            );

            auto color = material.calculateColor(worldPoint, normal, light, camera, uv);
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(screenPoint, color);
        }
    }
}

static inline void fillTType2(const Point3 &w0, const Point3 &w1, const Point3 &w2, const Point3 &s0, const Point3 &s1, const Point3 &s2, const TexturePoint &t1, const TexturePoint &t2, const TexturePoint &t3, const Vector3 &n1, const Vector3 &n2, const Vector3 &n3, const TexturedMaterial &material, const Light &light, const Camera &camera)
{
    auto yStart = static_cast<int>(s0.y());
    auto yEnd = static_cast<int>(s2.y());
    auto dx0 = s1.x() - s0.x();
    auto dy0 = s1.y() - s0.y();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            Point3 point(x + 0.5f, y + 0.5f, 0.0f);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());
            Point3 worldPoint(
                barycentric.interpolate(w0.x(), w1.x(), w2.x()),
                barycentric.interpolate(w0.y(), w1.y(), w2.y()),
                barycentric.interpolate(w0.z(), w1.z(), w2.z())
            );
            Point3 screenPoint(x, y, z);
            Vector3 normal(
                barycentric.interpolate(n1.x(), n2.x(), n3.x()),
                barycentric.interpolate(n1.y(), n2.y(), n3.y()),
                barycentric.interpolate(n1.z(), n2.z(), n3.z())
            );
            TexturePoint uv(
                barycentric.interpolate(t1.getX(), t2.getX(), t3.getX()),
                barycentric.interpolate(t1.getY(), t2.getY(), t3.getY())
            );

            auto color = material.calculateColor(worldPoint, normal, light, camera, uv);
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(screenPoint, color);
        }
    }
}

static inline void fillTType3LowerPart(const Point3 &w0, const Point3 &w1, const Point3 &w2, const Point3 &s0, const Point3 &s1, const Point3 &s2, const TexturePoint &t1, const TexturePoint &t2, const TexturePoint &t3, const Vector3 &n1, const Vector3 &n2, const Vector3 &n3, const TexturedMaterial &material, const Light &light, const Camera &camera)
{
    auto yStart = static_cast<int>(s0.y());
    auto yEnd = static_cast<int>(s1.y());
    auto dx0 = s1.x() - s0.x();
    auto dy0 = s1.y() - s0.y();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            Point3 point(x + 0.5f, y + 0.5f, 0.0f);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());
            Point3 worldPoint(
                barycentric.interpolate(w0.x(), w1.x(), w2.x()),
                barycentric.interpolate(w0.y(), w1.y(), w2.y()),
                barycentric.interpolate(w0.z(), w1.z(), w2.z())
            );
            Point3 screenPoint(x, y, z);
            Vector3 normal(
                barycentric.interpolate(n1.x(), n2.x(), n3.x()),
                barycentric.interpolate(n1.y(), n2.y(), n3.y()),
                barycentric.interpolate(n1.z(), n2.z(), n3.z())
            );
            TexturePoint uv(
                barycentric.interpolate(t1.getX(), t2.getX(), t3.getX()),
                barycentric.interpolate(t1.getY(), t2.getY(), t3.getY())
            );

            auto color = material.calculateColor(worldPoint, normal, light, camera, uv);
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(screenPoint, color);
        }
    }
}

static inline void fillTType3UpperPart(const Point3 &w0, const Point3 &w1, const Point3 &w2, const Point3 &s0, const Point3 &s1, const Point3 &s2, const TexturePoint &t1, const TexturePoint &t2, const TexturePoint &t3, const Vector3 &n1, const Vector3 &n2, const Vector3 &n3, const TexturedMaterial &material, const Light &light, const Camera &camera)
{
    auto yStart = static_cast<int>(s1.y());
    auto yEnd = static_cast<int>(s2.y());
    auto dx0 = s2.x() - s1.x();
    auto dy0 = s2.y() - s1.y();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();

    yStart = max(yStart, -1);
    yEnd = min(yEnd, WINDOW_HEIGHT);

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s1.y()) * dx0 / dy0 + s1.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;

        xStart = max(xStart, -1);
        xEnd = min(xEnd, WINDOW_WIDTH);

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            Point3 point(x + 0.5f, y + 0.5f, 0.0f);
            BarycentricPoint barycentric(s0, s1, s2, point);
            auto z = barycentric.interpolate(s0.z(), s1.z(), s2.z());
            Point3 worldPoint(
                barycentric.interpolate(w0.x(), w1.x(), w2.x()),
                barycentric.interpolate(w0.y(), w1.y(), w2.y()),
                barycentric.interpolate(w0.z(), w1.z(), w2.z())
            );
            Point3 screenPoint(x, y, z);
            Vector3 normal(
                barycentric.interpolate(n1.x(), n2.x(), n3.x()),
                barycentric.interpolate(n1.y(), n2.y(), n3.y()),
                barycentric.interpolate(n1.z(), n2.z(), n3.z())
            );
            TexturePoint uv(
                barycentric.interpolate(t1.getX(), t2.getX(), t3.getX()),
                barycentric.interpolate(t1.getY(), t2.getY(), t3.getY())
            );

            auto color = material.calculateColor(worldPoint, normal, light, camera, uv);
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(screenPoint, color);
        }
    }
}

static inline float simplePow128(float x)
{
    auto pow2 = x * x;
    auto pow4 = pow2 * pow2;
    auto pow8 = pow4 * pow4;
    auto pow16 = pow8 * pow8;
    auto pow32 = pow16 * pow16;
    auto pow64 = pow32 * pow32;
    return pow64 * pow64;
}

static inline void calculateColor(const Point3 &point, const Vector3 &normal, const Material &material, const Light &light, const Camera &camera, VertexColor *output)
{
    Vector3 lightDirection;
    lightDirection.asProduct(light.getDir(), -1.0f);
    Vector3 viewDirection;
    viewDirection.asDifference(camera.getPos(), point);
    Vector3 halfVector;
    halfVector.asSum(lightDirection, viewDirection).normalize();

    VertexColor lightColor;
    lightColor.asProduct(light.getColor(), light.getIntensity());

    auto theta = normal * lightDirection;
    VertexColor diffuse;
    diffuse.asProduct(lightColor, material.getDiffuse()).asProduct(diffuse, theta > 0.0f ? theta : 0.0f);

    auto alpha = normal * halfVector;
    if(alpha > 1.0f)
    {
        alpha = 1.0f;
    }
    VertexColor specular;
    specular.asProduct(lightColor, material.getSpecular()).asProduct(specular, alpha > 0.0f ? simplePow128(alpha) : 0.0f);

    VertexColor ambient;
    ambient.asProduct(lightColor, material.getAmbient());

    output->copy(diffuse).asSum(*output, specular).asSum(*output, ambient).restrictColor();
}

void Model::fillTriangle(Point3 &s0, Point3 &s1, Point3 &s2, Color color)
{

    if(s0.y() > s1.y())
    {
        std::swap(s0, s1);
    }
    if(s0.y() > s2.y())
    {
        std::swap(s0, s2);
    }
    if(s1.y() > s2.y())
    {
        std::swap(s1, s2);
    }

    if(static_cast<int>(s0.y()) == static_cast<int>(s1.y()))
    {
        fillType1(s0, s1, s2, color);
    }
    else if(static_cast<int>(s1.y()) == static_cast<int>(s2.y()))
    {
        fillType2(s0, s1, s2, color);
    }
    else
    {
        fillType3LowerPart(s0, s1, s2, color);
        fillType3UpperPart(s0, s1, s2, color);
    }
}

void Model::fillTriangleWithVertexColor(Point3 &s0, Point3 &s1, Point3 &s2, VertexColor &c0, VertexColor &c1, VertexColor &c2)
{
    if(s0.y() > s1.y())
    {
        std::swap(s0, s1);
        std::swap(c0, c1);
    }
    if(s0.y() > s2.y())
    {
        std::swap(s0, s2);
        std::swap(c0, c2);
    }
    if(s1.y() > s2.y())
    {
        std::swap(s1, s2);
        std::swap(c1, c2);
    }

        if(static_cast<int>(s0.y()) == static_cast<int>(s1.y()))
    {
        fillVType1(s0, s1, s2, c0, c1, c2);
    }
    else if(static_cast<int>(s1.y()) == static_cast<int>(s2.y()))
    {
        fillVType2(s0, s1, s2, c0, c1, c2);
    }
    else
    {
        fillVType3LowerPart(s0, s1, s2, c0, c1, c2);
        fillVType3UpperPart(s0, s1, s2, c0, c1, c2);
    }
}

void Model::fillTriangleWithTexture(Point3 &w0, Point3 &w1, Point3 &w2, Point3 &s0, Point3 &s1, Point3 &s2, TexturePoint &t0, TexturePoint &t1, TexturePoint &t2, Vector3 &n0, Vector3 &n1, Vector3 &n2, const TexturedMaterial &texture, Light light, Camera camera)
{
    if(s0.y() > s1.y())
    {
        std::swap(w0, w1);
        std::swap(s0, s1);
        std::swap(t0, t1);
        std::swap(n0, n1);
    }
    if(s0.y() > s2.y())
    {
        std::swap(w0, w2);
        std::swap(s0, s2);
        std::swap(t0, t2);
        std::swap(n0, n2);
    }
    if(s1.y() > s2.y())
    {
        std::swap(w1, w2);
        std::swap(s1, s2);
        std::swap(t1, t2);
        std::swap(n1, n2);
    }

    if(static_cast<int>(s0.y()) == static_cast<int>(s1.y()))
    {
        fillTType1(w0, w1, w2, s0, s1, s2, t0, t1, t2, n0, n1, n2, texture, light, camera);
    }
    else if(static_cast<int>(s1.y()) == static_cast<int>(s2.y()))
    {
        fillTType2(w0, w1, w2, s0, s1, s2, t0, t1, t2, n0, n1, n2, texture, light, camera);
    }
    else
    {
        fillTType3LowerPart(w0, w1, w2, s0, s1, s2, t0, t1, t2, n0, n1, n2, texture, light, camera);
        fillTType3UpperPart(w0, w1, w2, s0, s1, s2, t0, t1, t2, n0, n1, n2, texture, light, camera);
    }
}

void Model::renderAsWireframe(const Camera &camera, Color color)
{
    for (Triangle &triangle : triangles)
    {
        const Point3 &p0 = getVertex(triangle, 0).getPos();
        const Point3 &p1 = getVertex(triangle, 1).getPos();
        const Point3 &p2 = getVertex(triangle, 2).getPos();

        Point3 w0, w1, w2;
        w0.asProduct(transform, p0);
        w1.asProduct(transform, p1);
        w2.asProduct(transform, p2);

        Renderer::INSTANCE.renderWorldSpaceLine(w0, w1, camera, color);
        Renderer::INSTANCE.renderWorldSpaceLine(w1, w2, camera, color);
        Renderer::INSTANCE.renderWorldSpaceLine(w2, w0, camera, color);
    }
}

void Model::renderAswireframeWithoutBackface(const Camera &camera, Color color)
{
    for (Triangle &triangle : triangles)
    {
        const Point3 &p0 = getVertex(triangle, 0).getPos();
        const Point3 &p1 = getVertex(triangle, 1).getPos();
        const Point3 &p2 = getVertex(triangle, 2).getPos();
        Point3 w0, w1, w2;
        Point3 temp;
        Point3 s0, s1, s2;
        w0.asProduct(transform, p0);
        temp.asProduct(camera.getWorldToView(), w0);
        s0.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        w1.asProduct(transform, p1);
        temp.asProduct(camera.getWorldToView(), w1);
        s1.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        w2.asProduct(transform, p2);
        temp.asProduct(camera.getWorldToView(), w2);
        s2.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();

        if((s1.x() - s0.x()) * (s2.y() - s0.y()) - (s1.y() - s0.y()) * (s2.x() - s0.x()) > 0)
        {
            continue;
        }

        Renderer::INSTANCE.renderWorldSpaceLine(w0, w1, camera, color);
        Renderer::INSTANCE.renderWorldSpaceLine(w1, w2, camera, color);
        Renderer::INSTANCE.renderWorldSpaceLine(w2, w0, camera, color);
    }
}

void Model::simpleRender(const Camera &camera, Color wireFrameColor, Color fillColor)
{
    for (Triangle &triangle : triangles)
    {
        const Point3 &p0 = getVertex(triangle, 0).getPos();
        const Point3 &p1 = getVertex(triangle, 1).getPos();
        const Point3 &p2 = getVertex(triangle, 2).getPos();
        Point3 w0, w1, w2;
        Point3 temp;
        Point3 s0, s1, s2;
        w0.asProduct(transform, p0);
        temp.asProduct(camera.getWorldToView(), w0);
        s0.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        w1.asProduct(transform, p1);
        temp.asProduct(camera.getWorldToView(), w1);
        s1.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        w2.asProduct(transform, p2);
        temp.asProduct(camera.getWorldToView(), w2);
        s2.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();

        if((s1.x() - s0.x()) * (s2.y() - s0.y()) - (s1.y() - s0.y()) * (s2.x() - s0.x()) > 0)
        {
            continue;
        }

        fillTriangle(s0, s1, s2, fillColor);
        Renderer::INSTANCE.renderWorldSpaceLine(w0, w1, camera, wireFrameColor);
        Renderer::INSTANCE.renderWorldSpaceLine(w1, w2, camera, wireFrameColor);
        Renderer::INSTANCE.renderWorldSpaceLine(w2, w0, camera, wireFrameColor);
    }
}

void Model::updateNormals()
{
    for (Triangle &triangle : triangles)
    {
        const Point3 &p0 = getVertex(triangle, 0).getPos();
        const Point3 &p1 = getVertex(triangle, 1).getPos();
        const Point3 &p2 = getVertex(triangle, 2).getPos();
        Vector3 v0(p1.x() - p0.x(), p1.y() - p0.y(), p1.z() - p0.z());
        Vector3 v1(p2.x() - p0.x(), p2.y() - p0.y(), p2.z() - p0.z());
        Vector3 normal;
        normal.asProduct(v0, v1).normalize();

        getVertex(triangle, 0).normal.asSum(getVertex(triangle, 0).normal, normal);
        getVertex(triangle, 1).normal.asSum(getVertex(triangle, 1).normal, normal);
        getVertex(triangle, 2).normal.asSum(getVertex(triangle, 2).normal, normal);
    }

    for (Vertex &vertex : vertices)
    {
        vertex.normal = vertex.normal.normalize();
    }
}

void Model::renderWithMaterial(const Camera &camera, const Material &material, const Light &light)
{
    for (Triangle &triangle : triangles)
    {
        const Point3 &p0 = getVertex(triangle, 0).getPos();
        const Point3 &p1 = getVertex(triangle, 1).getPos();
        const Point3 &p2 = getVertex(triangle, 2).getPos();
        Point3 w0, w1, w2;
        Vector3 n0, n1, n2;
        Point3 temp;
        Point3 s0, s1, s2;
        w0.asProduct(transform, p0);
        n0.asProduct(transform, getVertex(triangle, 0).normal).normalize();
        temp.asProduct(camera.getWorldToView(), w0);
        s0.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        w1.asProduct(transform, p1);
        n1.asProduct(transform, getVertex(triangle, 1).normal).normalize();
        temp.asProduct(camera.getWorldToView(), w1);
        s1.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        w2.asProduct(transform, p2);
        n2.asProduct(transform, getVertex(triangle, 2).normal).normalize();
        temp.asProduct(camera.getWorldToView(), w2);
        s2.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();

        if((s1.x() - s0.x()) * (s2.y() - s0.y()) - (s1.y() - s0.y()) * (s2.x() - s0.x()) > 0)
        {
            continue;
        }

        VertexColor c0, c1, c2;
        calculateColor(w0, n0, material, light, camera, &c0);
        calculateColor(w1, n1, material, light, camera, &c1);
        calculateColor(w2, n2, material, light, camera, &c2);

        fillTriangleWithVertexColor(s0, s1, s2, c0, c1, c2);
    }
}

void Model::renderWithTexture(const Camera &camera, const TexturedMaterial &material, const Light &light)
{
    for (Triangle &triangle : triangles)
    {
        const Point3 &p0 = getVertex(triangle, 0).getPos();
        const Point3 &p1 = getVertex(triangle, 1).getPos();
        const Point3 &p2 = getVertex(triangle, 2).getPos();
        Point3 w0, w1, w2;
        Vector3 n0, n1, n2;
        Point3 temp;
        Point3 s0, s1, s2;
        w0.asProduct(transform, p0);
        n0.asProduct(transform, getVertex(triangle, 0).normal).normalize();
        temp.asProduct(camera.getWorldToView(), w0);
        s0.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        w1.asProduct(transform, p1);
        n1.asProduct(transform, getVertex(triangle, 1).normal).normalize();
        temp.asProduct(camera.getWorldToView(), w1);
        s1.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        w2.asProduct(transform, p2);
        n2.asProduct(transform, getVertex(triangle, 2).normal).normalize();
        temp.asProduct(camera.getWorldToView(), w2);
        s2.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();

        if((s1.x() - s0.x()) * (s2.y() - s0.y()) - (s1.y() - s0.y()) * (s2.x() - s0.x()) > 0)
        {
            continue;
        }

        TexturePoint t0, t1, t2;
        t0 = getTexture(triangle, 0);
        t1 = getTexture(triangle, 1);
        t2 = getTexture(triangle, 2);

        fillTriangleWithTexture(w0, w1, w2, s0, s1, s2, t0, t1, t2, n0, n1, n2, material, light, camera);
    }
}