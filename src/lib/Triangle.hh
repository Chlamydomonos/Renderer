#pragma once

class Triangle
{
private:
    int v1;
    int v2;
    int v3;
public:
    Triangle() = default;
    Triangle(int v1, int v2, int v3) : v1(v1), v2(v2), v3(v3) {}
    int getV1() const
    {
        return v1;
    }
    int getV2() const
    {
        return v2;
    }
    int getV3() const
    {
        return v3;
    }
};