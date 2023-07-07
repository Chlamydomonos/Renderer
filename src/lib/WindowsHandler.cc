#include "WindowsHandler.hh"

#include "Renderer.hh"
#include "Controller.hh"

#include <cstdio>

WindowsHandler WindowsHandler::INSTANCE;

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
    if(key == VK_SPACE)
    {
        Controller::INSTANCE.onSpaceDown();
    }
    else if(key == 'W')
    {
        Controller::INSTANCE.onWDown();
    }
}

void WindowsHandler::onKeyUp(Window window, Key key)
{
    ScopedLock lock(renderMutex);
    if(key == VK_SPACE)
    {
        Controller::INSTANCE.onSpaceUp();
    }
    else if(key == 'W')
    {
        Controller::INSTANCE.onWUp();
    }
}