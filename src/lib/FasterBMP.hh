#pragma once

#include "windows.hh"
#include "VertexColor.hh"

class FasterBMP
{
private:
    char *bits;
    int width;
    int height;
    BITMAPINFO bi;
public:
    FasterBMP()
    {
        width = WINDOW_WIDTH;
        height = WINDOW_HEIGHT;
        bits = new char[width * height * 3];
        for(int i = 0; i < width * height * 3; i++)
            bits[i] = 0;

        bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bi.bmiHeader.biWidth = width;
        bi.bmiHeader.biHeight = -height;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 24;
        bi.bmiHeader.biCompression = BI_RGB;
        bi.bmiHeader.biSizeImage = width * height * 3;
        bi.bmiHeader.biClrUsed = 0;
	    bi.bmiHeader.biClrImportant = 0;
    }

    ~FasterBMP()
    {
        delete[] bits;
    }

    void setPixel(int x, int y, char r, char g, char b)
    {
        bits[(y * width + x) * 3 + 0] = b;
        bits[(y * width + x) * 3 + 1] = g;
        bits[(y * width + x) * 3 + 2] = r;
    }

    void setPixel(int x, int y, Color color)
    {
        bits[(y * width + x) * 3 + 0] = GetBValue(color);
        bits[(y * width + x) * 3 + 1] = GetGValue(color);
        bits[(y * width + x) * 3 + 2] = GetRValue(color);
    }

    void render(PaintDevice canvas)
    {
        SetDIBitsToDevice(canvas, 0, 0, width, height, 0, 0, 0, height, bits, &bi, DIB_RGB_COLORS);
    }

    void clear()
    {
        for(int i = 0; i < width * height * 3; i++)
            bits[i] = 0;
    }
};