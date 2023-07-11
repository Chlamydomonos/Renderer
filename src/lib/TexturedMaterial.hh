#pragma once

#include "windows.hh"
#include "Light.hh"
#include "geometry3.hh"
#include "TexturePoint.hh"
#include "Camera.hh"

#include <memory>
#include <stdexcept>

class BMPBuffer
{
private:
    VertexColor *buffer;
    int width;
    int height;
    friend class TexturedMaterial;
public:
    BMPBuffer() : buffer(nullptr), width(0), height(0) {}

    BMPBuffer(int width, int height) : width(width), height(height)
    {
        buffer = new VertexColor[width * height];
    }

    ~BMPBuffer()
    {
        if(buffer != nullptr)
        {
            delete[] buffer;
        }
    }
    const VertexColor &operator()(int x, int y) const
    {
        return buffer[y * width + x];
    }
};

class TexturedMaterial
{
private:
    float ambient;
    Bitmap diffuse;
    float specular;
    int width;
    int height;
    std::unique_ptr<BMPBuffer> buffer;
public:
    TexturedMaterial(Bitmap image) : ambient(0.2f), diffuse(image), specular(0.2f)
    {
        BITMAP bm;
        GetObject(image, sizeof(bm), &bm);
        width = bm.bmWidth;
        height = bm.bmHeight;

        BITMAPINFO bi;
	    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	    bi.bmiHeader.biWidth = bm.bmWidth;
	    bi.bmiHeader.biHeight = -bm.bmHeight;
	    bi.bmiHeader.biPlanes = 1;
	    bi.bmiHeader.biBitCount = bm.bmBitsPixel;
	    bi.bmiHeader.biCompression = BI_RGB;
	    bi.bmiHeader.biSizeImage = bm.bmWidth * bm.bmHeight * bm.bmBitsPixel / 8;
	    bi.bmiHeader.biClrUsed = 0;
	    bi.bmiHeader.biClrImportant = 0;


        buffer = std::make_unique<BMPBuffer>(width, height);
        auto dc = GetDC(NULL);
        auto tempBuffer = new BYTE[width * height * bm.bmBitsPixel / 8];
        bool success = GetDIBits(dc, image, 0, height, tempBuffer, &bi, DIB_RGB_COLORS);
        if(!success)
        {
            throw std::runtime_error("Failed to get DIBits");
        }

        for (int i = 0; i < width * height; i++)
        {
            auto color = RGB(tempBuffer[i * 3 + 2], tempBuffer[i * 3 + 1], tempBuffer[i * 3]);
            buffer->buffer[i].fromColor(color);
        }
        delete[] tempBuffer;
    }

    Color calculateColor(const Point3 &point, const Vector3 &normal, const Light &light, const Camera &camera, const TexturePoint &uv) const;
};