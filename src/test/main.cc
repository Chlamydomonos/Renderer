#include "geometry3.hh"
#include "Camera.hh"

#include <cstdio>

constexpr float PI = 3.14159265358979323846f;

int main()
{
    Point3 p1(0.0f, 0.0f, 10.0f);
    Point3 p2(0.0f, 0.0f, 5.0f);
    Point3 p3(0.0f, 0.0f, -5.0f);
    Point3 p4(0.0f, 0.0f, -10.0f);
    Camera camera;
    Point3 c1, c2, c3, c4, s1, s2, s3, s4;
    c1.asProduct(camera.getWorldToView(), p1);
    c2.asProduct(camera.getWorldToView(), p2);
    c3.asProduct(camera.getWorldToView(), p3);
    c4.asProduct(camera.getWorldToView(), p4);
    s1.asProduct(camera.getViewToScreen(), c1);
    s2.asProduct(camera.getViewToScreen(), c2);
    s3.asProduct(camera.getViewToScreen(), c3);
    s4.asProduct(camera.getViewToScreen(), c4);
    printf("s1: %f, %f, %f\n", s1.x(), s1.y(), s1.z());
    printf("s2: %f, %f, %f\n", s2.x(), s2.y(), s2.z());
    printf("s3: %f, %f, %f\n", s3.x(), s3.y(), s3.z());
    printf("s4: %f, %f, %f\n", s4.x(), s4.y(), s4.z());
    return 0;
}