#pragma once

class Controller
{
private:
    Controller() = default;
    friend class WindowsHandler;

    bool spaceDown = false;
    int spaceSignals = 0;

    void onSpaceDown()
    {
        spaceDown = true;
    }

    void onSpaceUp()
    {
        spaceDown = false;
        spaceSignals++;
    }

    bool wDown = false;
    int wSignals = 0;

    void onWDown()
    {
        wDown = true;
    }

    void onWUp()
    {
        wDown = false;
        wSignals++;
    }
public:
    static Controller INSTANCE;

    bool tryGetSpaceSignal()
    {
        if (spaceSignals > 0)
        {
            spaceSignals--;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool tryGetWSignal()
    {
        if (wSignals > 0)
        {
            wSignals--;
            return true;
        }
        else
        {
            return false;
        }
    }
};