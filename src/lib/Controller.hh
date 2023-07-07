#pragma once

class Controller
{
private:
    Controller() = default;
    friend class WindowsHandler;
    bool wDown = false;
    bool aDown = false;
    bool sDown = false;
    bool dDown = false;
    bool spaceDown = false;
    bool shiftDown = false;
    bool upDown = false;
    bool downDown = false;
    bool leftDown = false;
    bool rightDown = false;
public:
    static Controller INSTANCE;

    bool isWDown() const
    {
        return wDown;
    }

    bool isADown() const
    {
        return aDown;
    }

    bool isSDown() const
    {
        return sDown;
    }

    bool isDDown() const
    {
        return dDown;
    }

    bool isSpaceDown() const
    {
        return spaceDown;
    }

    bool isShiftDown() const
    {
        return shiftDown;
    }

    bool isUpDown() const
    {
        return upDown;
    }

    bool isDownDown() const
    {
        return downDown;
    }

    bool isLeftDown() const
    {
        return leftDown;
    }

    bool isRightDown() const
    {
        return rightDown;
    }
};