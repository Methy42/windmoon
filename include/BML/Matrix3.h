#ifndef BML_MATRIX3_H
#define BML_MATRIX3_H

#include <cmath>
#include "BML/Vector3.h"

class Matrix3 {
public:
    // 构造函数
    Matrix3();
    Matrix3(float m11, float m12, float m13,
            float m21, float m22, float m23,
            float m31, float m32, float m33);
    // 拷贝构造函数
    Matrix3(const Matrix3& m);

    // 矩阵加法
    Matrix3 operator+(const Matrix3& m) const;
    // 矩阵减法
    Matrix3 operator-(const Matrix3& m) const;
    // 矩阵乘法
    Matrix3 operator*(const Matrix3& m) const;

    // 矩阵标量乘法
    Matrix3 operator*(float c) const;
    // 矩阵标量除法
    Matrix3 operator/(float c) const;

    // 矩阵转置
    Matrix3 transpose() const;
    // 矩阵求逆
    Matrix3 inverse() const;

    // 获取矩阵元素
    float get(int row, int col) const;
    // 设置矩阵元素
    void set(int row, int col, float val);

private:
    float m_data[3][3];
};

#endif // BML_MATRIX3_H
