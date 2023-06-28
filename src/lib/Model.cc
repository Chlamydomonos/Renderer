#include "Model.hh"

#include "Renderer.hh"

void Model::renderAsWireframe(const Camera &camera, PaintDevice canvas, Color color)
{
    for (Triangle &triangle : triangles)
    {
        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 0).getPos(), getVertex(triangle, 1).getPos(), camera, canvas, color);
        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 1).getPos(), getVertex(triangle, 2).getPos(), camera, canvas, color);
        Renderer::INSTANCE.renderWorldSpaceLine(getVertex(triangle, 2).getPos(), getVertex(triangle, 0).getPos(), camera, canvas, color);
    }
}