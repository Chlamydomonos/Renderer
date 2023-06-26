#pragma once

#include <cmath>

/**
 * @brief 2D矩阵，用齐次坐标表示
 */
class Matrix2
{
private:
    float data[3][3] = {0.0f};
public:
    Matrix2() = default;
    Matrix2(float a, float b, float c, float d) : data{{a, b, 0.0f}, {c, d, 0.0f}, {0.0f, 0.0f, 1.0f}} {}
    Matrix2(float e, float f) : data{{1.0f, 0.0f, e}, {0.0f, 1.0f, f}, {0.0f, 0.0f, 1.0f}} {}

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix2 &identity()
    {
        data[0][0] = 1.0f;
        data[1][1] = 1.0f;
        data[2][2] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix2 &translate(float x, float y)
    {
        data[0][0] = 1.0f;
        data[1][1] = 1.0f;
        data[2][2] = 1.0f;
        data[0][2] = x;
        data[1][2] = y;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix2 &scale(float r)
    {
        data[0][0] = r;
        data[1][1] = r;
        data[2][2] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix2 &scale(float x, float y)
    {
        data[0][0] = x;
        data[1][1] = y;
        data[2][2] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix2 &rotate(float theta)
    {
        auto cosTheta = cos(theta);
        auto sinTheta = sin(theta);
        data[0][0] = cosTheta;
        data[0][1] = -sinTheta;
        data[1][0] = sinTheta;
        data[1][1] = cosTheta;
        data[2][2] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix2 &reflectX()
    {
        data[0][0] = 1.0f;
        data[1][1] = -1.0f;
        data[2][2] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix2 &reflectY()
    {
        data[0][0] = -1.0f;
        data[1][1] = 1.0f;
        data[2][2] = 1.0f;
        return *this;
    }

    Matrix2 &thenTranslate(float x, float y)
    {
        data[0][2] += data[0][0] * x + data[0][1] * y;
        data[1][2] += data[1][0] * x + data[1][1] * y;
        data[2][2] += data[2][0] * x + data[2][1] * y;
        return *this;
    }

    Matrix2 &thenScale(float r)
    {
        data[0][0] *= r;
        data[0][1] *= r;
        data[1][0] *= r;
        data[1][1] *= r;
        data[2][0] *= r;
        data[2][1] *= r;
        return *this;
    }

    Matrix2 &thenScale(float x, float y)
    {
        data[0][0] *= x;
        data[0][1] *= y;
        data[1][0] *= x;
        data[1][1] *= y;
        data[2][0] *= x;
        data[2][1] *= y;
        return *this;
    }

    Matrix2 &thenRotate(float theta)
    {
        auto cosTheta = cos(theta);
        auto sinTheta = sin(theta);
        auto a = data[0][0];
        auto b = data[0][1];
        auto c = data[1][0];
        auto d = data[1][1];
        data[0][0] = a * cosTheta + b * sinTheta;
        data[0][1] = -a * sinTheta + b * cosTheta;
        data[1][0] = c * cosTheta + d * sinTheta;
        data[1][1] = -c * sinTheta + d * cosTheta;
        data[2][0] = data[2][0] * cosTheta + data[2][1] * sinTheta;
        data[2][1] = -data[2][0] * sinTheta + data[2][1] * cosTheta;
        return *this;
    }

    Matrix2 &thenReflectX()
    {
        data[0][1] = -data[0][1];
        data[1][0] = -data[1][0];
        data[2][1] = -data[2][1];
        return *this;
    }

    Matrix2 &thenReflectY()
    {
        data[0][0] = -data[0][0];
        data[1][1] = -data[1][1];
        data[2][0] = -data[2][0];
        return *this;
    }
};