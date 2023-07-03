#include "Model.hh"

#include "Renderer.hh"

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
    auto dz0 = s2.z() - s0.z();
    auto dx1 = s2.x() - s1.x();
    auto dy1 = s2.y() - s1.y();
    auto dz1 = s2.z() - s1.z();

    for(int y = yStart + 1; y < yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s1.y()) * dx1 / dy1 + s1.x());
        auto z0 = (y - s0.y()) * dz0 / dy0 + s0.z();
        auto z1 = (y - s1.y()) * dz1 / dy1 + s1.z();
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;
        auto zStart = z1 < z0 ? z0 : z1;
        auto zEnd = z1 < z0 ? z1 : z0;

        for(int x = xStart + 1; x < xEnd; x++)
        {
            auto z = zStart + (x - xStart) / (xEnd - xStart) * (zEnd - zStart);
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
    auto dz0 = s1.z() - s0.z();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();
    auto dz1 = s2.z() - s0.z();

    for(int y = yStart + 1; y < yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto z0 = (y - s0.y()) * dz0 / dy0 + s0.z();
        auto z1 = (y - s0.y()) * dz1 / dy1 + s0.z();
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;
        auto zStart = z1 < z0 ? z0 : z1;
        auto zEnd = z1 < z0 ? z1 : z0;

        for(int x = xStart + 1; x < xEnd; x++)
        {
            auto z = zStart + (x - xStart) / (xEnd - xStart) * (zEnd - zStart);
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
    auto dz0 = s1.z() - s0.z();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();
    auto dz1 = s2.z() - s0.z();

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto z0 = (y - s0.y()) * dz0 / dy0 + s0.z();
        auto z1 = (y - s0.y()) * dz1 / dy1 + s0.z();
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;
        auto zStart = z1 < z0 ? z0 : z1;
        auto zEnd = z1 < z0 ? z1 : z0;

        for(int x = xStart + 1; x < xEnd; x++)
        {
            auto z = zStart + (x - xStart) / (xEnd - xStart) * (zEnd - zStart);
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
    auto dz0 = s2.z() - s1.z();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();
    auto dz1 = s2.z() - s0.z();

    for(int y = yStart + 1; y < yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s1.y()) * dx0 / dy0 + s1.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto z0 = (y - s1.y()) * dz0 / dy0 + s1.z();
        auto z1 = (y - s0.y()) * dz1 / dy1 + s0.z();
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;
        auto zStart = z1 < z0 ? z0 : z1;
        auto zEnd = z1 < z0 ? z1 : z0;

        for(int x = xStart + 1; x < xEnd; x++)
        {
            auto z = zStart + (x - xStart) / (xEnd - xStart) * (zEnd - zStart);
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
    auto dz0 = s2.z() - s0.z();
    auto dx1 = s2.x() - s1.x();
    auto dy1 = s2.y() - s1.y();
    auto dz1 = s2.z() - s1.z();

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s1.y()) * dx1 / dy1 + s1.x());
        auto z0 = (y - s0.y()) * dz0 / dy0 + s0.z();
        auto z1 = (y - s1.y()) * dz1 / dy1 + s1.z();
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;
        auto zStart = z1 < z0 ? z0 : z1;
        auto zEnd = z1 < z0 ? z1 : z0;

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            auto z = zStart + (x - xStart) / (xEnd - xStart) * (zEnd - zStart);
            Point3 point(x, y, z);
            Point3 barycentric;
            barycentric.asBarycentric(s0, s1, s2, point);
            VertexColor color0, color1, color2;
            color0.asProduct(c0, barycentric.x());
            color1.asProduct(c1, barycentric.y());
            color2.asProduct(c2, barycentric.z());
            color0.asSum(color0, color1).asSum(color0, color2);
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(point, color0.toColor());
        }
    }
}

static inline void fillVType2(const Point3 &s0, const Point3 &s1, const Point3 &s2, VertexColor &c0, VertexColor &c1, VertexColor &c2)
{
    auto yStart = static_cast<int>(s0.y());
    auto yEnd = static_cast<int>(s2.y());
    auto dx0 = s1.x() - s0.x();
    auto dy0 = s1.y() - s0.y();
    auto dz0 = s1.z() - s0.z();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();
    auto dz1 = s2.z() - s0.z();

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto z0 = (y - s0.y()) * dz0 / dy0 + s0.z();
        auto z1 = (y - s0.y()) * dz1 / dy1 + s0.z();
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;
        auto zStart = z1 < z0 ? z0 : z1;
        auto zEnd = z1 < z0 ? z1 : z0;

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            auto z = zStart + (x - xStart) / (xEnd - xStart) * (zEnd - zStart);
            Point3 point(x, y, z);
            Point3 barycentric;
            barycentric.asBarycentric(s0, s1, s2, point);
            VertexColor color0, color1, color2;
            color0.asProduct(c0, barycentric.x());
            color1.asProduct(c1, barycentric.y());
            color2.asProduct(c2, barycentric.z());
            color0.asSum(color0, color1).asSum(color0, color2);
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(point, color0.toColor());
        }
    }
}

static inline void fillVType3LowerPart(const Point3 &s0, const Point3 &s1, const Point3 &s2, VertexColor &c0, VertexColor &c1, VertexColor &c2)
{
    auto yStart = static_cast<int>(s0.y());
    auto yEnd = static_cast<int>(s1.y());
    auto dx0 = s1.x() - s0.x();
    auto dy0 = s1.y() - s0.y();
    auto dz0 = s1.z() - s0.z();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();
    auto dz1 = s2.z() - s0.z();

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s0.y()) * dx0 / dy0 + s0.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto z0 = (y - s0.y()) * dz0 / dy0 + s0.z();
        auto z1 = (y - s0.y()) * dz1 / dy1 + s0.z();
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;
        auto zStart = z1 < z0 ? z0 : z1;
        auto zEnd = z1 < z0 ? z1 : z0;

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            auto z = zStart + (x - xStart) / (xEnd - xStart) * (zEnd - zStart);
            Point3 point(x, y, z);
            Point3 barycentric;
            barycentric.asBarycentric(s0, s1, s2, point);
            VertexColor color0, color1, color2;
            color0.asProduct(c0, barycentric.x());
            color1.asProduct(c1, barycentric.y());
            color2.asProduct(c2, barycentric.z());
            color0.asSum(color0, color1).asSum(color0, color2);
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(point, color0.toColor());
        }
    }
}

static inline void fillVType3UpperPart(const Point3 &s0, const Point3 &s1, const Point3 &s2, VertexColor &c0, VertexColor &c1, VertexColor &c2)
{
    auto yStart = static_cast<int>(s1.y());
    auto yEnd = static_cast<int>(s2.y());
    auto dx0 = s2.x() - s1.x();
    auto dy0 = s2.y() - s1.y();
    auto dz0 = s2.z() - s1.z();
    auto dx1 = s2.x() - s0.x();
    auto dy1 = s2.y() - s0.y();
    auto dz1 = s2.z() - s0.z();

    for(int y = yStart + 1; y <= yEnd; y++)
    {
        auto x0 = static_cast<int>((y - s1.y()) * dx0 / dy0 + s1.x());
        auto x1 = static_cast<int>((y - s0.y()) * dx1 / dy1 + s0.x());
        auto z0 = (y - s1.y()) * dz0 / dy0 + s1.z();
        auto z1 = (y - s0.y()) * dz1 / dy1 + s0.z();
        auto xStart = x0 < x1 ? x0 : x1;
        auto xEnd = x0 < x1 ? x1 : x0;
        auto zStart = z1 < z0 ? z0 : z1;
        auto zEnd = z1 < z0 ? z1 : z0;

        for(int x = xStart + 1; x <= xEnd; x++)
        {
            auto z = zStart + (x - xStart) / (xEnd - xStart) * (zEnd - zStart);
            Point3 point(x, y, z);
            Point3 barycentric;
            barycentric.asBarycentric(s0, s1, s2, point);
            VertexColor color0, color1, color2;
            color0.asProduct(c0, barycentric.x());
            color1.asProduct(c1, barycentric.y());
            color2.asProduct(c2, barycentric.z());
            color0.asSum(color0, color1).asSum(color0, color2);
            Renderer::INSTANCE.renderScreenSpacePointWithZBuffer(point, color0.toColor());
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
    VertexColor specular;
    specular.asProduct(lightColor, material.getSpecular()).asProduct(specular, alpha > 0.0f ? simplePow128(alpha) : 0.0f);

    VertexColor ambient;
    ambient.asProduct(lightColor, material.getAmbient());

    output->copy(diffuse).asSum(*output, specular).asSum(*output, ambient);
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

void Model::renderAsWireframe(const Camera &camera, Color color)
{
    for (Triangle &triangle : triangles)
    {
        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 0).getPos(), getVertex(triangle, 1).getPos(), camera, color);
        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 1).getPos(), getVertex(triangle, 2).getPos(), camera, color);
        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 2).getPos(), getVertex(triangle, 0).getPos(), camera, color);
    }
}

void Model::renderAswireframeWithoutBackface(const Camera &camera, Color color)
{
    for (Triangle &triangle : triangles)
    {
        const Point3 &p0 = getVertex(triangle, 0).getPos();
        const Point3 &p1 = getVertex(triangle, 1).getPos();
        const Point3 &p2 = getVertex(triangle, 2).getPos();
        Point3 temp;
        Point3 s0, s1, s2;
        temp.asProduct(camera.getWorldToView(), p0);
        s0.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        temp.asProduct(camera.getWorldToView(), p1);
        s1.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        temp.asProduct(camera.getWorldToView(), p2);
        s2.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();

        if((s1.x() - s0.x()) * (s2.y() - s0.y()) - (s1.y() - s0.y()) * (s2.x() - s0.x()) > 0)
        {
            continue;
        }

        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 0).getPos(), getVertex(triangle, 1).getPos(), camera, color);
        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 1).getPos(), getVertex(triangle, 2).getPos(), camera, color);
        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 2).getPos(), getVertex(triangle, 0).getPos(), camera, color);
    }
}

void Model::simpleRender(const Camera &camera, Color wireFrameColor, Color fillColor)
{
    for (Triangle &triangle : triangles)
    {
        const Point3 &p0 = getVertex(triangle, 0).getPos();
        const Point3 &p1 = getVertex(triangle, 1).getPos();
        const Point3 &p2 = getVertex(triangle, 2).getPos();
        Point3 temp;
        Point3 s0, s1, s2;
        temp.asProduct(camera.getWorldToView(), p0);
        s0.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        temp.asProduct(camera.getWorldToView(), p1);
        s1.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        temp.asProduct(camera.getWorldToView(), p2);
        s2.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();

        if((s1.x() - s0.x()) * (s2.y() - s0.y()) - (s1.y() - s0.y()) * (s2.x() - s0.x()) > 0)
        {
            continue;
        }

        fillTriangle(s0, s1, s2, fillColor);
        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 0).getPos(), getVertex(triangle, 1).getPos(), camera, wireFrameColor);
        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 1).getPos(), getVertex(triangle, 2).getPos(), camera, wireFrameColor);
        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 2).getPos(), getVertex(triangle, 0).getPos(), camera, wireFrameColor);
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
        triangle.normal.copy(normal);

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
        Point3 temp;
        Point3 s0, s1, s2;
        temp.asProduct(camera.getWorldToView(), p0);
        s0.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        temp.asProduct(camera.getWorldToView(), p1);
        s1.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();
        temp.asProduct(camera.getWorldToView(), p2);
        s2.asProduct(camera.getViewToScreen(), temp).moveToPixelCenter();

        if((s1.x() - s0.x()) * (s2.y() - s0.y()) - (s1.y() - s0.y()) * (s2.x() - s0.x()) > 0)
        {
            continue;
        }

        VertexColor c0, c1, c2;
        calculateColor(p0, getVertex(triangle, 0).normal, material, light, camera, &c0);
        calculateColor(p1, getVertex(triangle, 1).normal, material, light, camera, &c1);
        calculateColor(p2, getVertex(triangle, 2).normal, material, light, camera, &c2);

        fillTriangleWithVertexColor(s0, s1, s2, c0, c1, c2);
    }
}