#include "geometry3.hh"
#include "Camera.hh"

constexpr float PI = 3.14159265358979323846f;

int main()
{
    Point3 p1(0.0f, 0.0f, 9.0f);
    Point3 p2(-1.0f, 0.0f, 10.0f);
    Point3 p3(1.0f, 0.0f, 10.0f);
    Point3 p4(0.0f, -1.0f, 10.0f);
    Point3 p5(0.0f, 1.0f, 10.0f);
    Point3 p6(0.0f, 0.0f, 11.0f);
    Camera camera;
    Point3 c1;
    c1.asProduct(camera.getWorldToView(), p1);
    Point3 c2;
    c2.asProduct(camera.getWorldToView(), p2);
    Point3 c3;
    c3.asProduct(camera.getWorldToView(), p3);
    Point3 c4;
    c4.asProduct(camera.getWorldToView(), p4);
    Point3 c5;
    c5.asProduct(camera.getWorldToView(), p5);
    Point3 c6;
    c6.asProduct(camera.getWorldToView(), p6);
    return 0;
}