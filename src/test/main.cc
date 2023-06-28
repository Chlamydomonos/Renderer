#include "geometry3.hh"
#include "Camera.hh"

#include <cstdio>

constexpr float PI = 3.14159265358979323846f;

int main()
{
    Point3 p1(-1.0f, -1.0f, 9.0f);
    Point3 p2(1.0f, -1.0f, 9.0f);
    Point3 p3(-1.0f, -1.0f, 9.2f);
    Point3 p4(1.0f, -1.0f, 9.2f);
    Point3 p5(-1.0f, -0.8f, 9.0f);
    Point3 p6(1.0f, -0.8f, 9.0f);
    Camera camera;
    camera.setPos(Point3(0.0f, 2.0f, 0.0f));
    camera.setDir(Vector3(sin(0.3), sin(-PI / 12.0f), cos(0.3)));
    camera.setUp(Vector3(0.0f, cos(-PI / 12.0f), 0.0f));
    Point3 c1, c2, c3, c4, c5, c6, s1, s2, s3, s4, s5, s6;
    c1.asProduct(camera.getWorldToView(), p1);
    s1.asProduct(camera.getViewToScreen(), c1);
    c2.asProduct(camera.getWorldToView(), p2);
    s2.asProduct(camera.getViewToScreen(), c2);
    c3.asProduct(camera.getWorldToView(), p3);
    s3.asProduct(camera.getViewToScreen(), c3);
    c4.asProduct(camera.getWorldToView(), p4);
    s4.asProduct(camera.getViewToScreen(), c4);
    c5.asProduct(camera.getWorldToView(), p5);
    s5.asProduct(camera.getViewToScreen(), c5);
    c6.asProduct(camera.getWorldToView(), p6);
    s6.asProduct(camera.getViewToScreen(), c6);
    printf("p1: %f, %f, %f; c1: %f, %f, %f; s1: %f, %f, %f\n", p1.x(), p1.y(), p1.z(), c1.x(), c1.y(), c1.z(), s1.x(), s1.y(), s1.z());
    printf("p2: %f, %f, %f; c2: %f, %f, %f; s2: %f, %f, %f\n", p2.x(), p2.y(), p2.z(), c2.x(), c2.y(), c2.z(), s2.x(), s2.y(), s2.z());
    printf("p3: %f, %f, %f; c3: %f, %f, %f; s3: %f, %f, %f\n", p3.x(), p3.y(), p3.z(), c3.x(), c3.y(), c3.z(), s3.x(), s3.y(), s3.z());
    printf("p4: %f, %f, %f; c4: %f, %f, %f; s4: %f, %f, %f\n", p4.x(), p4.y(), p4.z(), c4.x(), c4.y(), c4.z(), s4.x(), s4.y(), s4.z());
    printf("p5: %f, %f, %f; c5: %f, %f, %f; s5: %f, %f, %f\n", p5.x(), p5.y(), p5.z(), c5.x(), c5.y(), c5.z(), s5.x(), s5.y(), s5.z());
    printf("p6: %f, %f, %f; c6: %f, %f, %f; s6: %f, %f, %f\n", p6.x(), p6.y(), p6.z(), c6.x(), c6.y(), c6.z(), s6.x(), s6.y(), s6.z());
    return 0;
}