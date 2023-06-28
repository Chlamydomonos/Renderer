#include "Model.hh"

#include "Renderer.hh"

static inline void fillType1(const Point3 &s0, const Point3 &s1, const Point3 &s2, const Camera &camera, Color color)
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

static inline void fillType2(const Point3 &s0, const Point3 &s1, const Point3 &s2, const Camera &camera, Color color)
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

static inline void fillType3LowerPart(const Point3 &s0, const Point3 &s1, const Point3 &s2, const Camera &camera, Color color)
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

static inline void fillType3UpperPart(const Point3 &s0, const Point3 &s1, const Point3 &s2, const Camera &camera, Color color)
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

void Model::fillTriangle(const Triangle &triangle, const Camera &camera, Color color)
{
    auto p0 = getVertex(triangle, 0).getPos();
    auto p1 = getVertex(triangle, 1).getPos();
    auto p2 = getVertex(triangle, 2).getPos();
    Point3 temp;
    Point3 s0, s1, s2;
    temp.asProduct(camera.getWorldToView(), p0);
    s0.asProduct(camera.getViewToScreen(), temp);
    temp.asProduct(camera.getWorldToView(), p1);
    s1.asProduct(camera.getViewToScreen(), temp);
    temp.asProduct(camera.getWorldToView(), p2);
    s2.asProduct(camera.getViewToScreen(), temp);

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
        fillType1(s0, s1, s2, camera, color);
    }
    else if(static_cast<int>(s1.y()) == static_cast<int>(s2.y()))
    {
        fillType2(s0, s1, s2, camera, color);
    }
    else
    {
        fillType3LowerPart(s0, s1, s2, camera, color);
        fillType3UpperPart(s0, s1, s2, camera, color);
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

void Model::simpleRender(const Camera &camera, Color wireFrameColor, Color fillColor)
{
    for (Triangle &triangle : triangles)
    {
        fillTriangle(triangle, camera, fillColor);
        Renderer::INSTANCE.renderWorldSpaceLineWithZBuffer(getVertex(triangle, 0).getPos(), getVertex(triangle, 1).getPos(), camera, wireFrameColor);
        Renderer::INSTANCE.renderWorldSpaceLineWithZBuffer(getVertex(triangle, 1).getPos(), getVertex(triangle, 2).getPos(), camera, wireFrameColor);
        Renderer::INSTANCE.renderWorldSpaceLineWithZBuffer(getVertex(triangle, 2).getPos(), getVertex(triangle, 0).getPos(), camera, wireFrameColor);
    }
}