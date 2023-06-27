#include "geometry3.hh"

constexpr float PI = 3.14159265358979323846f;

int main()
{
    Point3 px1(1, 0, 1);
    Matrix3 mx1;
    mx1.roll(PI / 2.0f);
    Point3 px2;
    px2.asProduct(mx1, px1);
    Matrix3 mx2;
    mx2.identity().thenRoll(PI / 2.0f);
    Point3 px3;
    px3.asProduct(mx2, px1);
    Point3 py1(0, 1, 1);
    Matrix3 my1;
    my1.pitch(PI / 2.0f);
    Point3 py2;
    py2.asProduct(my1, py1);
    Matrix3 my2;
    my2.rotate(PI / 2.0f, 0, 1, 0);
    Point3 py3;
    py3.asProduct(my2, py1);
    Point3 pz1(-1, 0, 1);
    Matrix3 mz1;
    mz1.yaw(PI / 2.0f);
    Point3 pz2;
    pz2.asProduct(mz1, pz1);
    Matrix3 mz2;
    mz2.rotate(PI / 2.0f, 0, 0, 1);
    Point3 pz3;
    pz3.asProduct(mz2, pz1);
    return 0;
}