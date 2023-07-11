#pragma once

#include "windows.hh"
#include <thread>
#include <mutex>
#include <condition_variable>

using ScopedLock = std::scoped_lock<std::mutex>;
using UniqueLock = std::unique_lock<std::mutex>;

class WindowsHandler
{
private:
    WindowsHandler() {}
    WindowsHandler(const WindowsHandler&) = delete;
    WindowsHandler &operator=(const WindowsHandler&) = delete;

    std::thread renderThread;
    std::mutex renderMutex;
    std::condition_variable renderCond;
    PaintDevice canvas;
    Bitmap bmp;
    bool threadRunning = true;
    bool rendering = false;
    HINSTANCE instance;
    friend int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
    float currentFPS;
public:
    static WindowsHandler INSTANCE;

    void onCreate(Window window);
    void onPaint(Window window, PaintDevice device);
    void onDestroy(Window window);
    void onClose(Window window);
    void onTimer(Window window);
    void onKeyDown(Window window, Key key);
    void onKeyUp(Window window, Key key);
    HINSTANCE getInstance()
    {
        return instance;
    }
};