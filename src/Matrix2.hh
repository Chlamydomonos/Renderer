#pragma once

class Matrix2
{
private:
    float data[3][3] = {0.0f};
public:
    Matrix2() = default;
    Matrix2(float a, float b, float c, float d) : data{{a, b, 0.0f}, {c, d, 0.0f}, {0.0f, 0.0f, 1.0f}} {}
    Matrix2(float e, float f) : data{{1.0f, 0.0f, e}, {0.0f, 1.0f, f}, {0.0f, 0.0f, 1.0f}} {}
};