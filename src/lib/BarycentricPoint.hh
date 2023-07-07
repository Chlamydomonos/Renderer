#pragma once

#include "geometry3.hh"

class BarycentricPoint
{
private:
    float alpha;
    float beta;
    float gamma;
    float factor;
public:
    BarycentricPoint(Point3 a, Point3 b, Point3 c, Point3 p)
    {
        gamma = (a.y() - b.y()) * p.x() + (b.x() - a.x()) * p.y() + a.x() * b.y() - b.x() * a.y();
        gamma /= (a.y() - b.y()) * c.x() + (b.x() - a.x()) * c.y() + a.x() * b.y() - b.x() * a.y();

        beta = (a.y() - c.y()) * p.x() + (c.x() - a.x()) * p.y() + a.x() * c.y() - c.x() * a.y();
        beta /= (a.y() - c.y()) * b.x() + (c.x() - a.x()) * b.y() + a.x() * c.y() - c.x() * a.y();

        alpha = 1.0f - beta - gamma;

        factor = 1.0f / (alpha / a.w() + beta / b.w() + gamma / c.w());

        alpha /= a.w();
        beta /= b.w();
        gamma /= c.w();
    }

    float getAlpha() const
    {
        return alpha;
    }

    float getBeta() const
    {
        return beta;
    }

    float getGamma() const
    {
        return gamma;
    }

    float getFactor() const
    {
        return factor;
    }

    float interpolate(float a, float b, float c) const
    {
        return factor * (alpha * a + beta * b + gamma * c);
    }
};