#pragma once

#include <cmath>

/**
 * @brief 左手系下的3D矩阵，用齐次坐标表示
 */
class Matrix3
{
private:
    float data[4][4] = {0.0f};
    friend class Point3;
    friend class Vector3;
public:
    Matrix3() = default;
    Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i) : data{{a, b, c, 0.0f}, {d, e, f, 0.0f}, {g, h, i, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}} {}
    Matrix3(float j, float k, float l) : data{{1.0f, 0.0f, 0.0f, j}, {0.0f, 1.0f, 0.0f, k}, {0.0f, 0.0f, 1.0f, l}, {0.0f, 0.0f, 0.0f, 1.0f}} {}

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix3 &translate(float x, float y, float z)
    {
        data[0][0] = 1.0f;
        data[1][1] = 1.0f;
        data[2][2] = 1.0f;
        data[3][3] = 1.0f;
        data[0][3] = x;
        data[1][3] = y;
        data[2][3] = z;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix3 &scale(float r)
    {
        data[0][0] = r;
        data[1][1] = r;
        data[2][2] = r;
        data[3][3] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix3 &scale(float x, float y, float z)
    {
        data[0][0] = x;
        data[1][1] = y;
        data[2][2] = z;
        data[3][3] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix3 &roll(float theta)
    {
        auto cosTheta = cos(theta);
        auto sinTheta = sin(theta);

        data[0][0] = 1.0f;
        data[1][1] = cosTheta;
        data[1][2] = sinTheta;
        data[2][1] = -sinTheta;
        data[2][2] = cosTheta;
        data[3][3] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix3 &pitch(float theta)
    {
        auto cosTheta = cos(theta);
        auto sinTheta = sin(theta);
        data[0][0] = cosTheta;
        data[0][2] = sinTheta;
        data[1][1] = 1.0f;
        data[2][0] = -sinTheta;
        data[2][2] = cosTheta;
        data[3][3] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix3 &yaw(float theta)
    {
        auto cosTheta = cos(theta);
        auto sinTheta = sin(theta);
        data[0][0] = cosTheta;
        data[0][1] = -sinTheta;
        data[1][0] = sinTheta;
        data[1][1] = cosTheta;
        data[2][2] = 1.0f;
        data[3][3] = 1.0f;
        return *this;
    }
};