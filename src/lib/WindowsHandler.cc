#include "WindowsHandler.hh"

#include "Renderer.hh"
#include "Controller.hh"

#include <cstdio>
#include <string>

WindowsHandler WindowsHandler::INSTANCE;

static LARGE_INTEGER lastTime;

void WindowsHandler::onCreate(Window window)
{
    SetTimer(window, TIMER_ID, 1000 / FPS, NULL);
    Renderer::INSTANCE.init();

    renderThread = std::thread([&]() {
        while(threadRunning)
        {
            UniqueLock lock(renderMutex);
            Renderer::INSTANCE.render(canvas);
            rendering = false;
            renderCond.wait(lock, [&]() { return rendering || !threadRunning; });
        }
    });
}

void WindowsHandler::onPaint(Window window, PaintDevice device)
{
    {
        ScopedLock lock(renderMutex);

        if(canvas != NULL)
        {
            auto str = std::to_string(currentFPS);
            DrawText(canvas, str.c_str(), -1, new RECT{ 0, 0, 200, 200 }, DT_LEFT);

            BitBlt(device, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, canvas, 0, 0, SRCCOPY);

    	    DeleteDC(canvas);
	        DeleteObject(bmp);
        }

        canvas = CreateCompatibleDC(device);
        bmp = CreateCompatibleBitmap(device, WINDOW_WIDTH, WINDOW_HEIGHT);

        RECT wholeRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	    FillRect(canvas, &wholeRect, CreateSolidBrush(RGB(0, 0, 0)));
        SelectObject(canvas, bmp);

        rendering = true;
        LARGE_INTEGER currentTime, frequency;
        QueryPerformanceCounter(&currentTime);
        QueryPerformanceFrequency(&frequency);
        currentFPS = (float)frequency.QuadPart / (currentTime.QuadPart - lastTime.QuadPart);
        lastTime = currentTime;
    }
    renderCond.notify_one();
}

void WindowsHandler::onDestroy(Window window)
{
    {
        ScopedLock lock(renderMutex);
        threadRunning = false;
    }
    renderCond.notify_one();
    renderThread.join();
}

void WindowsHandler::onClose(Window window)
{
    {
        ScopedLock lock(renderMutex);
        threadRunning = false;
    }
    renderCond.notify_one();
    renderThread.join();
}

void WindowsHandler::onTimer(Window window)
{
    RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	InvalidateRect(window, &rect, TRUE);
}

void WindowsHandler::onKeyDown(Window window, Key key)
{
    ScopedLock lock(renderMutex);
    switch(key)
    {
    case 'W':
        Controller::INSTANCE.wDown = true;
        break;
    case 'A':
        Controller::INSTANCE.aDown = true;
        break;
    case 'S':
        Controller::INSTANCE.sDown = true;
        break;
    case 'D':
        Controller::INSTANCE.dDown = true;
        break;
    case VK_SPACE:
        Controller::INSTANCE.spaceDown = true;
        break;
    case VK_SHIFT:
        Controller::INSTANCE.shiftDown = true;
        break;
    case VK_UP:
        Controller::INSTANCE.upDown = true;
        break;
    case VK_DOWN:
        Controller::INSTANCE.downDown = true;
        break;
    case VK_LEFT:
        Controller::INSTANCE.leftDown = true;
        break;
    case VK_RIGHT:
        Controller::INSTANCE.rightDown = true;
        break;
    case 'I':
        Controller::INSTANCE.iDown = true;
        break;
    case 'K':
        Controller::INSTANCE.kDown = true;
        break;
    case 'J':
        Controller::INSTANCE.jDown = true;
        break;
    case 'L':
        Controller::INSTANCE.lDown = true;
        break;
    case 'Q':
        Controller::INSTANCE.qDown = true;
        break;
    case 'E':
        Controller::INSTANCE.eDown = true;
        break;
    default:
        break;
    }
}

void WindowsHandler::onKeyUp(Window window, Key key)
{
    ScopedLock lock(renderMutex);
    switch(key)
    {
    case 'W':
        Controller::INSTANCE.wDown = false;
        break;
    case 'A':
        Controller::INSTANCE.aDown = false;
        break;
    case 'S':
        Controller::INSTANCE.sDown = false;
        break;
    case 'D':
        Controller::INSTANCE.dDown = false;
        break;
    case VK_SPACE:
        Controller::INSTANCE.spaceDown = false;
        break;
    case VK_SHIFT:
        Controller::INSTANCE.shiftDown = false;
        break;
    case VK_UP:
        Controller::INSTANCE.upDown = false;
        break;
    case VK_DOWN:
        Controller::INSTANCE.downDown = false;
        break;
    case VK_LEFT:
        Controller::INSTANCE.leftDown = false;
        break;
    case VK_RIGHT:
        Controller::INSTANCE.rightDown = false;
        break;
    case 'I':
        Controller::INSTANCE.iDown = false;
        break;
    case 'K':
        Controller::INSTANCE.kDown = false;
        break;
    case 'J':
        Controller::INSTANCE.jDown = false;
        break;
    case 'L':
        Controller::INSTANCE.lDown = false;
        break;
    case 'Q':
        Controller::INSTANCE.qDown = false;
        break;
    case 'E':
        Controller::INSTANCE.eDown = false;
        break;
    case '1':
        Controller::INSTANCE.signals[0]++;
        break;
    case '2':
        Controller::INSTANCE.signals[1]++;
        break;
    case '3':
        Controller::INSTANCE.signals[2]++;
        break;
    case '4':
        Controller::INSTANCE.signals[3]++;
        break;
    case '5':
        Controller::INSTANCE.signals[4]++;
        break;
    case '6':
        Controller::INSTANCE.signals[5]++;
        break;
    case '7':
        Controller::INSTANCE.signals[6]++;
        break;
    case '8':
        Controller::INSTANCE.signals[7]++;
        break;
    case '9':
        Controller::INSTANCE.signals[8]++;
        break;
    case '0':
        Controller::INSTANCE.signals[9]++;
        break;
    default:
        break;
    }
}