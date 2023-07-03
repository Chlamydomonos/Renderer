#pragma once

#include "geometry3.hh"

class Triangle
{
private:
    int v0;
    int v1;
    int v2;
    friend class Model;
public:
    Triangle() = default;
    Triangle(int v0, int v1, int v2) : v0(v0), v1(v1), v2(v2) {}
    int getV0() const
    {
        return v0;
    }
    int getV1() const
    {
        return v1;
    }
    int getV2() const
    {
        return v2;
    }
};