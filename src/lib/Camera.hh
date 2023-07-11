#pragma once

#include "geometry3.hh"

#include "windows.hh"
#include "FPController.hh"

class Camera
{
private:
    Point3 pos{0.0f, 0.0f, 0.0f};
    Vector3 dir{0.0f, 0.0f, 1.0f};
    Vector3 up{0.0f, 1.0f, 0.0f};
    Matrix3 worldToView;
    Matrix3 viewToScreen;
    float fovY = 3.14159265358979323846f / 3.0f;
    float l;
    float r;
    float b;
    float t;
    float n = -0.5f;
    float f = -100.0f;

    void calculateLRBT()
    {
        float height = WINDOW_HEIGHT;
        float width = WINDOW_WIDTH;

        t = -n * tan(fovY / 2.0f);
        b = -t;
        r = t * width / height;
        l = -r;
    }

    void calculateWorldToView()
    {
        Vector3 right;
        right.asProduct(dir, up).normalize();

        Matrix3 t(-pos.x(), -pos.y(), -pos.z());

        Matrix3 r(
            -right.x(), -right.y(), -right.z(),
            up.x(), up.y(), up.z(),
            -dir.x(), -dir.y(), -dir.z()
        );
        worldToView.asProduct(r, t);
    }

    void calculateViewToScreen()
    {
        Matrix3 p1;
        p1.perspective(n, f);

        Matrix3 p2;
        p2.orthographic(l, r, b, t, n, f);

        Matrix3 p3;
        p3.scale(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 1.0f).thenTranslate(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 1.0f);

        Matrix3 temp;
        temp.asProduct(p3, p2);
        viewToScreen.asProduct(temp, p1);
    }

public:
    Camera()
    {
        calculateLRBT();
        calculateWorldToView();
        calculateViewToScreen();
    }

    Camera(const Point3 &pos, const Vector3 &dir, const Vector3 &up, float fovY = 3.14159265358979323846f / 3.0f) :
    pos(pos), dir(dir), up(up), fovY(fovY)
    {
        calculateLRBT();
        calculateWorldToView();
        calculateViewToScreen();
    }

    const Point3 &getPos() const
    {
        return pos;
    }

    const Vector3 &getDir() const
    {
        return dir;
    }

    const Vector3 &getUp() const
    {
        return up;
    }

    void setPos(const Point3 &pos)
    {
        this->pos.copy(pos);
        calculateWorldToView();
    }

    void setDir(const Vector3 &dir)
    {
        this->dir.copy(dir).normalize();
        calculateWorldToView();
    }

    void setUp(const Vector3 &up)
    {
        this->up.copy(up).normalize();
        calculateWorldToView();
    }

    void setFovY(float fovY)
    {
        this->fovY = fovY;
        calculateLRBT();
        calculateViewToScreen();
    }

    void apply(const Matrix3 &matrix)
    {
        Point3 temp;
        temp.asProduct(matrix, pos);
        pos.copy(temp);
        Vector3 temp2;
        temp2.asProduct(matrix, dir);
        dir.copy(temp2);
        temp2.asProduct(matrix, up);
        up.copy(temp2);
        calculateWorldToView();
    }

    const Matrix3 &getWorldToView() const
    {
        return worldToView;
    }

    const Matrix3 &getViewToScreen() const
    {
        return viewToScreen;
    }

    void fromFPController(const FPController &controller)
    {
        pos.copy(controller.getPos());
        dir.copy(controller.getFront());
        up.copy(controller.getUp());
        calculateWorldToView();
    }
};