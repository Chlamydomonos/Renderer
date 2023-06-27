#pragma once

#include <Windows.h>

using Window = HWND;
using PaintDevice = HDC;
using Instance = HINSTANCE;
using Bitmap = HBITMAP;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 768
#define TIMER_ID 1
#define FPS 24