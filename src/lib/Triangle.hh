#pragma once

#include "geometry3.hh"

class Triangle
{
private:
    int v0;
    int v1;
    int v2;
    int t0;
    int t1;
    int t2;
    friend class Model;
public:
    Triangle() = default;
    Triangle(int v0, int v1, int v2) : v0(v0), v1(v1), v2(v2), t0(-1), t1(-1), t2(-1) {}
    Triangle(int v0, int v1, int v2, int t0, int t1, int t2) : v0(v0), v1(v1), v2(v2), t0(t0), t1(t1), t2(t2) {}
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
    int getT0() const
    {
        return t0;
    }
    int getT1() const
    {
        return t1;
    }
    int getT2() const
    {
        return t2;
    }
};