#pragma once

#include "windows.hh"

class Renderer
{
private:
    Renderer() {}
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
public:
    static Renderer INSTANCE;
    void render(PaintDevice canvas);
};