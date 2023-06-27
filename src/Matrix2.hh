#pragma once

#include <cmath>

/**
 * @brief 2D矩阵，用齐次坐标表示
 */
class Matrix2
{
private:
    float data[3][3] = {0.0f};
    friend class Point2;
    friend class Vector2;
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
        data[0][0] += x * data[2][0];
        data[0][1] += x * data[2][1];
        data[0][2] += x * data[2][2];
        data[1][0] += y * data[2][0];
        data[1][1] += y * data[2][1];
        data[1][2] += y * data[2][2];
        return *this;
    }

    Matrix2 &thenScale(float r)
    {
        data[0][0] *= r;
        data[0][1] *= r;
        data[0][2] *= r;
        data[1][0] *= r;
        data[1][1] *= r;
        data[1][2] *= r;
        return *this;
    }

    Matrix2 &thenScale(float x, float y)
    {
        data[0][0] *= x;
        data[0][1] *= x;
        data[0][2] *= x;
        data[1][0] *= y;
        data[1][1] *= y;
        data[1][2] *= y;
        return *this;
    }

    Matrix2 &thenRotate(float theta)
    {
        auto sinTheta = sin(theta);
        auto cosTheta = cos(theta);
        auto a0 = data[0][0];
        auto a1 = data[0][1];
        auto a2 = data[0][2];
        auto b0 = data[1][0];
        auto b1 = data[1][1];
        auto b2 = data[1][2];
        data[0][0] = a0 * cosTheta - b0 * sinTheta;
        data[0][1] = a1 * cosTheta - b1 * sinTheta;
        data[0][2] = a2 * cosTheta - b2 * sinTheta;
        data[1][0] = a0 * sinTheta + b0 * cosTheta;
        data[1][1] = a1 * sinTheta + b1 * cosTheta;
        data[1][2] = a2 * sinTheta + b2 * cosTheta;
        return *this;
    }

    Matrix2 &thenReflectX()
    {
        data[1][0] = -data[1][0];
        data[1][1] = -data[1][1];
        data[1][2] = -data[1][2];
        return *this;
    }

    Matrix2 &thenReflectY()
    {
        data[0][0] = -data[0][0];
        data[0][1] = -data[0][1];
        data[0][2] = -data[0][2];
        return *this;
    }

    void asProduct(const Matrix2 &a, const Matrix2 &b)
    {
        auto a0 = a.data[0][0] * b.data[0][0] + a.data[0][1] * b.data[1][0] + a.data[0][2] * b.data[2][0];
        auto a1 = a.data[0][0] * b.data[0][1] + a.data[0][1] * b.data[1][1] + a.data[0][2] * b.data[2][1];
        auto a2 = a.data[0][0] * b.data[0][2] + a.data[0][1] * b.data[1][2] + a.data[0][2] * b.data[2][2];
        auto b0 = a.data[1][0] * b.data[0][0] + a.data[1][1] * b.data[1][0] + a.data[1][2] * b.data[2][0];
        auto b1 = a.data[1][0] * b.data[0][1] + a.data[1][1] * b.data[1][1] + a.data[1][2] * b.data[2][1];
        auto b2 = a.data[1][0] * b.data[0][2] + a.data[1][1] * b.data[1][2] + a.data[1][2] * b.data[2][2];
        auto c0 = a.data[2][0] * b.data[0][0] + a.data[2][1] * b.data[1][0] + a.data[2][2] * b.data[2][0];
        auto c1 = a.data[2][0] * b.data[0][1] + a.data[2][1] * b.data[1][1] + a.data[2][2] * b.data[2][1];
        auto c2 = a.data[2][0] * b.data[0][2] + a.data[2][1] * b.data[1][2] + a.data[2][2] * b.data[2][2];
        data[0][0] = a0;
        data[0][1] = a1;
        data[0][2] = a2;
        data[1][0] = b0;
        data[1][1] = b1;
        data[1][2] = b2;
        data[2][0] = c0;
        data[2][1] = c1;
        data[2][2] = c2;
    }

    const float operator()(int i, int j) const
    {
        return data[i][j];
    }

    float &operator()(int i, int j)
    {
        return data[i][j];
    }
};