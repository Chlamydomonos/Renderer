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
    bool iDown = false;
    bool kDown = false;
    bool jDown = false;
    bool lDown = false;
    bool qDown = false;
    bool eDown = false;
    int signals[10] = {0};
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

    bool isIDown() const
    {
        return iDown;
    }

    bool isKDown() const
    {
        return kDown;
    }

    bool isJDown() const
    {
        return jDown;
    }

    bool isLDown() const
    {
        return lDown;
    }

    bool isQDown() const
    {
        return qDown;
    }

    bool isEDown() const
    {
        return eDown;
    }

    bool tryGetSignal(int i)
    {
        if(signals[i] > 0)
        {
            signals[i]--;
            return true;
        }
        return false;
    }
};