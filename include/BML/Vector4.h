#ifndef BML_VECTOR4_H
#define BML_VECTOR4_H

#include <cmath>
#include "BML/Vector3.h"   // 三维向量类

class Vector4 {
public:
    // 构造函数
    Vector4();
    Vector4(float x, float y, float z, float w);
    // 拷贝构造函数
    Vector4(const Vector4& v);
    Vector4(const Vector3& v, float w);

    float x, y, z, w;

    // 向量加法
    Vector4 operator+(const Vector4& v) const;

    Vector4 operator-() const;  // 实现前置减号运算符

    // 向量减法
    Vector4 operator-(const Vector4& v) const;
    // 向量点乘
    float operator*(const Vector4& v) const;
    // 向量乘以标量
    Vector4 operator*(float scalar) const;
    // 向量除以标量
    Vector4 operator/(float scalar) const;
    // 向量叉乘
    Vector4 operator^(const Vector4& v) const;
    // 就地加法操作
    Vector4& operator+=(const Vector4& v);
    // 比较两个向量是否相等
    bool operator==(const Vector4& v) const;

    // 向量标准化
    Vector4 normalize() const;
    // 向量长度
    float length() const;
    // distanceTo函数 用于计算两个向量之间的距离
    float distanceTo(const Vector4& other) const;
    // lengthSquared 函数 用于计算向量长度的平方
    float lengthSquared() const;

    // 设置向量的x, y, z, w分量
    void set(float x, float y, float z, float w);

    static const Vector4 ZERO; // 静态常量 ZERO
    static const Vector4 UNIT_Z;  // 静态常量 UNIT_Z
    static const Vector4 UNIT_Y;  // 静态常量 UNIT_Y
    static const Vector4 UNIT_X;  // 静态常量 UNIT_X
    static const Vector4 UNIT_W;  // 静态常量 UNIT_W
};

#endif  // BML_VECTOR4_H