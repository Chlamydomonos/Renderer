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
    Matrix3 &identity()
    {
        data[0][0] = 1.0f;
        data[1][1] = 1.0f;
        data[2][2] = 1.0f;
        data[3][3] = 1.0f;
        return *this;
    }

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
        data[0][2] = -sinTheta;
        data[1][1] = 1.0f;
        data[2][0] = sinTheta;
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
        data[0][1] = sinTheta;
        data[1][0] = -sinTheta;
        data[1][1] = cosTheta;
        data[2][2] = 1.0f;
        data[3][3] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix3 &rotate(float theta, float x, float y, float z)
    {
        auto cosTheta = cos(theta);
        auto sinTheta = sin(theta);

        data[0][0] = cosTheta + (1 - cosTheta) * x * x;
        data[0][1] = (1 - cosTheta) * x * y + sinTheta * z;
        data[0][2] = (1 - cosTheta) * x * z - sinTheta * y;
        data[1][0] = (1 - cosTheta) * x * y - sinTheta * z;
        data[1][1] = cosTheta + (1 - cosTheta) * y * y;
        data[1][2] = (1 - cosTheta) * y * z + sinTheta * x;
        data[2][0] = (1 - cosTheta) * x * z + sinTheta * y;
        data[2][1] = (1 - cosTheta) * y * z - sinTheta * x;
        data[2][2] = cosTheta + (1 - cosTheta) * z * z;
        data[3][3] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix3 &rotate(float theta, const Vector3 &axis);

    Matrix3 &thenTranslate(float x, float y, float z)
    {
        data[0][0] += data[3][0] * x;
        data[0][1] += data[3][1] * x;
        data[0][2] += data[3][2] * x;
        data[0][3] += data[3][3] * x;
        data[1][0] += data[3][0] * y;
        data[1][1] += data[3][1] * y;
        data[1][2] += data[3][2] * y;
        data[1][3] += data[3][3] * y;
        data[2][0] += data[3][0] * z;
        data[2][1] += data[3][1] * z;
        data[2][2] += data[3][2] * z;
        data[2][3] += data[3][3] * z;
        return *this;
    }

    Matrix3 &thenScale(float r)
    {
        data[0][0] *= r;
        data[0][1] *= r;
        data[0][2] *= r;
        data[0][3] *= r;
        data[1][0] *= r;
        data[1][1] *= r;
        data[1][2] *= r;
        data[1][3] *= r;
        data[2][0] *= r;
        data[2][1] *= r;
        data[2][2] *= r;
        data[2][3] *= r;
        return *this;
    }

    Matrix3 &thenScale(float x, float y, float z)
    {
        data[0][0] *= x;
        data[0][1] *= x;
        data[0][2] *= x;
        data[0][3] *= x;
        data[1][0] *= y;
        data[1][1] *= y;
        data[1][2] *= y;
        data[1][3] *= y;
        data[2][0] *= z;
        data[2][1] *= z;
        data[2][2] *= z;
        data[2][3] *= z;
        return *this;
    }

    Matrix3 &thenRoll(float theta)
    {
        auto cosTheta = cos(theta);
        auto sinTheta = sin(theta);
        auto b0 = data[1][0];
        auto b1 = data[1][1];
        auto b2 = data[1][2];
        auto b3 = data[1][3];
        auto c0 = data[2][0];
        auto c1 = data[2][1];
        auto c2 = data[2][2];
        auto c3 = data[2][3];
        data[1][0] = b0 * cosTheta + c0 * sinTheta;
        data[1][1] = b1 * cosTheta + c1 * sinTheta;
        data[1][2] = b2 * cosTheta + c2 * sinTheta;
        data[1][3] = b3 * cosTheta + c3 * sinTheta;
        data[2][0] = c0 * cosTheta - b0 * sinTheta;
        data[2][1] = c1 * cosTheta - b1 * sinTheta;
        data[2][2] = c2 * cosTheta - b2 * sinTheta;
        data[2][3] = c3 * cosTheta - b3 * sinTheta;
        return *this;
    }

    Matrix3 &thenPitch(float theta)
    {
        auto cosTheta = cos(theta);
        auto sinTheta = sin(theta);
        auto a0 = data[0][0];
        auto a1 = data[0][1];
        auto a2 = data[0][2];
        auto a3 = data[0][3];
        auto c0 = data[2][0];
        auto c1 = data[2][1];
        auto c2 = data[2][2];
        auto c3 = data[2][3];
        data[0][0] = a0 * cosTheta - c0 * sinTheta;
        data[0][1] = a1 * cosTheta - c1 * sinTheta;
        data[0][2] = a2 * cosTheta - c2 * sinTheta;
        data[0][3] = a3 * cosTheta - c3 * sinTheta;
        data[2][0] = a0 * sinTheta + c0 * cosTheta;
        data[2][1] = a1 * sinTheta + c1 * cosTheta;
        data[2][2] = a2 * sinTheta + c2 * cosTheta;
        data[2][3] = a3 * sinTheta + c3 * cosTheta;
        return *this;
    }

    Matrix3 &thenYaw(float theta)
    {
        auto cosTheta = cos(theta);
        auto sinTheta = sin(theta);
        auto a0 = data[0][0];
        auto a1 = data[0][1];
        auto a2 = data[0][2];
        auto a3 = data[0][3];
        auto b0 = data[1][0];
        auto b1 = data[1][1];
        auto b2 = data[1][2];
        auto b3 = data[1][3];
        data[0][0] = a0 * cosTheta + b0 * sinTheta;
        data[0][1] = a1 * cosTheta + b1 * sinTheta;
        data[0][2] = a2 * cosTheta + b2 * sinTheta;
        data[0][3] = a3 * cosTheta + b3 * sinTheta;
        data[1][0] = b0 * cosTheta - a0 * sinTheta;
        data[1][1] = b1 * cosTheta - a1 * sinTheta;
        data[1][2] = b2 * cosTheta - a2 * sinTheta;
        data[1][3] = b3 * cosTheta - a3 * sinTheta;
        return *this;
    }

    Matrix3 &thenRotate(float theta, float x, float y, float z)
    {
        auto cosTheta = cos(theta);
        auto sinTheta = sin(theta);
        auto a0 = data[0][0];
        auto a1 = data[0][1];
        auto a2 = data[0][2];
        auto a3 = data[0][3];
        auto b0 = data[1][0];
        auto b1 = data[1][1];
        auto b2 = data[1][2];
        auto b3 = data[1][3];
        auto c0 = data[2][0];
        auto c1 = data[2][1];
        auto c2 = data[2][2];
        auto c3 = data[2][3];
        auto cosTheta1 = 1 - cosTheta;
        data[0][0] = a0 * (cosTheta1 * x * x + cosTheta) + b0 * (cosTheta1 * x * y - sinTheta * z) + c0 * (cosTheta1 * x * z + sinTheta * y);
        data[0][1] = a1 * (cosTheta1 * x * x + cosTheta) + b1 * (cosTheta1 * x * y - sinTheta * z) + c1 * (cosTheta1 * x * z + sinTheta * y);
        data[0][2] = a2 * (cosTheta1 * x * x + cosTheta) + b2 * (cosTheta1 * x * y - sinTheta * z) + c2 * (cosTheta1 * x * z + sinTheta * y);
        data[0][3] = a3 * (cosTheta1 * x * x + cosTheta) + b3 * (cosTheta1 * x * y - sinTheta * z) + c3 * (cosTheta1 * x * z + sinTheta * y);
        data[1][0] = a0 * (cosTheta1 * x * y - sinTheta * z) + b0 * (cosTheta1 * y * y + cosTheta) + c0 * (cosTheta1 * y * z + sinTheta * x);
        data[1][1] = a1 * (cosTheta1 * x * y - sinTheta * z) + b1 * (cosTheta1 * y * y + cosTheta) + c1 * (cosTheta1 * y * z + sinTheta * x);
        data[1][2] = a2 * (cosTheta1 * x * y - sinTheta * z) + b2 * (cosTheta1 * y * y + cosTheta) + c2 * (cosTheta1 * y * z + sinTheta * x);
        data[1][3] = a3 * (cosTheta1 * x * y - sinTheta * z) + b3 * (cosTheta1 * y * y + cosTheta) + c3 * (cosTheta1 * y * z + sinTheta * x);
        data[2][0] = a0 * (cosTheta1 * x * z + sinTheta * y) + b0 * (cosTheta1 * y * z - sinTheta * x) + c0 * (cosTheta1 * z * z + cosTheta);
        data[2][1] = a1 * (cosTheta1 * x * z + sinTheta * y) + b1 * (cosTheta1 * y * z - sinTheta * x) + c1 * (cosTheta1 * z * z + cosTheta);
        data[2][2] = a2 * (cosTheta1 * x * z + sinTheta * y) + b2 * (cosTheta1 * y * z - sinTheta * x) + c2 * (cosTheta1 * z * z + cosTheta);
        data[2][3] = a3 * (cosTheta1 * x * z + sinTheta * y) + b3 * (cosTheta1 * y * z - sinTheta * x) + c3 * (cosTheta1 * z * z + cosTheta);
        return *this;
    }

    Matrix3 &thenRotate(float theta, const Vector3 &axis);

    /**
     * @note 此函数的参数不能是this
     */
    Matrix3 &asProduct(const Matrix3 &a, const Matrix3 &b)
    {
        data[0][0] = a.data[0][0] * b.data[0][0] + a.data[0][1] * b.data[1][0] + a.data[0][2] * b.data[2][0] + a.data[0][3] * b.data[3][0];
        data[0][1] = a.data[0][0] * b.data[0][1] + a.data[0][1] * b.data[1][1] + a.data[0][2] * b.data[2][1] + a.data[0][3] * b.data[3][1];
        data[0][2] = a.data[0][0] * b.data[0][2] + a.data[0][1] * b.data[1][2] + a.data[0][2] * b.data[2][2] + a.data[0][3] * b.data[3][2];
        data[0][3] = a.data[0][0] * b.data[0][3] + a.data[0][1] * b.data[1][3] + a.data[0][2] * b.data[2][3] + a.data[0][3] * b.data[3][3];
        data[1][0] = a.data[1][0] * b.data[0][0] + a.data[1][1] * b.data[1][0] + a.data[1][2] * b.data[2][0] + a.data[1][3] * b.data[3][0];
        data[1][1] = a.data[1][0] * b.data[0][1] + a.data[1][1] * b.data[1][1] + a.data[1][2] * b.data[2][1] + a.data[1][3] * b.data[3][1];
        data[1][2] = a.data[1][0] * b.data[0][2] + a.data[1][1] * b.data[1][2] + a.data[1][2] * b.data[2][2] + a.data[1][3] * b.data[3][2];
        data[1][3] = a.data[1][0] * b.data[0][3] + a.data[1][1] * b.data[1][3] + a.data[1][2] * b.data[2][3] + a.data[1][3] * b.data[3][3];
        data[2][0] = a.data[2][0] * b.data[0][0] + a.data[2][1] * b.data[1][0] + a.data[2][2] * b.data[2][0] + a.data[2][3] * b.data[3][0];
        data[2][1] = a.data[2][0] * b.data[0][1] + a.data[2][1] * b.data[1][1] + a.data[2][2] * b.data[2][1] + a.data[2][3] * b.data[3][1];
        data[2][2] = a.data[2][0] * b.data[0][2] + a.data[2][1] * b.data[1][2] + a.data[2][2] * b.data[2][2] + a.data[2][3] * b.data[3][2];
        data[2][3] = a.data[2][0] * b.data[0][3] + a.data[2][1] * b.data[1][3] + a.data[2][2] * b.data[2][3] + a.data[2][3] * b.data[3][3];
        data[3][0] = a.data[3][0] * b.data[0][0] + a.data[3][1] * b.data[1][0] + a.data[3][2] * b.data[2][0] + a.data[3][3] * b.data[3][0];
        data[3][1] = a.data[3][0] * b.data[0][1] + a.data[3][1] * b.data[1][1] + a.data[3][2] * b.data[2][1] + a.data[3][3] * b.data[3][1];
        data[3][2] = a.data[3][0] * b.data[0][2] + a.data[3][1] * b.data[1][2] + a.data[3][2] * b.data[2][2] + a.data[3][3] * b.data[3][2];
        data[3][3] = a.data[3][0] * b.data[0][3] + a.data[3][1] * b.data[1][3] + a.data[3][2] * b.data[2][3] + a.data[3][3] * b.data[3][3];
        return *this;
    }

    Matrix3 &copy(const Matrix3 &a)
    {
        data[0][0] = a.data[0][0];
        data[0][1] = a.data[0][1];
        data[0][2] = a.data[0][2];
        data[0][3] = a.data[0][3];
        data[1][0] = a.data[1][0];
        data[1][1] = a.data[1][1];
        data[1][2] = a.data[1][2];
        data[1][3] = a.data[1][3];
        data[2][0] = a.data[2][0];
        data[2][1] = a.data[2][1];
        data[2][2] = a.data[2][2];
        data[2][3] = a.data[2][3];
        data[3][0] = a.data[3][0];
        data[3][1] = a.data[3][1];
        data[3][2] = a.data[3][2];
        data[3][3] = a.data[3][3];
        return *this;
    }

    const float &operator()(int i, int j) const
    {
        return data[i][j];
    }

    float &operator()(int i, int j)
    {
        return data[i][j];
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix3 &perspective(float n, float f)
    {
        data[0][0] = n;
        data[1][1] = n;
        data[2][2] = f + n;
        data[2][3] = -f * n;
        data[3][2] = 1.0f;
        return *this;
    }

    /**
     * @note 此函数只能在未初始化（使用默认构造函数创建）的矩阵上调用
     */
    Matrix3 &orthographic(float l, float r, float b, float t, float n, float f)
    {
        return translate(-(r + l) / 2.0f, -(t + b) / 2.0f, -(f + n) / 2.0f)
            .thenScale(2.0f / (r - l), 2.0f / (t - b), 2.0f / (f - n));
    }
};