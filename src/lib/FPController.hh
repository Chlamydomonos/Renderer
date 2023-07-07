#pragma once

#include "geometry3.hh"

class FPController
{
private:
    Point3 pos;
    float yaw;
    float pitch;
public:
    FPController() = default;

    void moveForward(float distance)
    {
        Vector3 dir(sin(yaw), 0.0f, cos(yaw));
        Vector3 dPos;
        dPos.asProduct(dir, distance);
        pos.asSum(pos, dPos);
    }

    void moveRight(float distance)
    {
        Vector3 dir(cos(yaw), 0.0f, -sin(yaw));
        Vector3 dPos;
        dPos.asProduct(dir, distance);
        pos.asSum(pos, dPos);
    }

    void moveUp(float distance)
    {
        pos.asSum(pos, Vector3(0.0f, distance, 0.0f));
    }

    void rotateYaw(float angle)
    {
        yaw += angle;
    }

    void rotatePitch(float angle)
    {
        pitch += angle;
    }

    const Point3 &getPos() const
    {
        return pos;
    }

    Vector3 getFront() const
    {
        return Vector3(sin(yaw) * cos(pitch), sin(pitch), cos(yaw) * cos(pitch));
    }

    Vector3 getUp() const
    {
        return Vector3(-sin(yaw) * sin(pitch), cos(pitch), -cos(yaw) * sin(pitch));
    }
};