#ifndef BML_VECTOR3_H
#define BML_VECTOR3_H

#include <cmath>

class Vector3 {
public:
    float x, y, z;

    // 构造函数
    Vector3();
    Vector3(float x, float y, float z);
    // 拷贝构造函数
    Vector3(const Vector3& v);

    // 向量加法
    Vector3 operator+(const Vector3& v) const;

    Vector3 operator-() const;  // 实现前置减号运算符

    // 向量减法
    Vector3 operator-(const Vector3& v) const;
    // 向量点乘
    float operator*(const Vector3& v) const;
    // 向量乘以标量
    Vector3 operator*(float scalar) const;
    // 向量除以标量
    Vector3 operator/(float scalar) const;
    // 向量叉乘
    Vector3 operator^(const Vector3& v) const;
    // 就地加法操作
    Vector3& operator+=(const Vector3& v);
    // 就地减法操作
    Vector3& operator-=(const Vector3& v);
    // 比较两个向量是否相等
    bool operator==(const Vector3& v) const;

    // 向量标准化
    Vector3 normalize() const;
    // 向量长度
    float length() const;
    // reflect函数 用于计算反射向量
    Vector3 reflect(const Vector3& normal) const;
    // distanceTo函数 用于计算两个向量之间的距离
    float distanceTo(const Vector3& other) const;
    // lengthSquared 函数 用于计算向量长度的平方
    float lengthSquared() const;

    // 设置向量的x, y, z分量
    void set(float x, float y, float z);

    static const Vector3 ZERO; // 静态常量 ZERO
    static const Vector3 UNIT_Z;  // 静态常量 UNIT_Z
    static const Vector3 UNIT_Y;  // 静态常量 UNIT_Y
    static const Vector3 UNIT_X;  // 静态常量 UNIT_X
    static const Vector3 UNIT_SCALE;  // 静态常量 UNIT_SCALE
};

#endif // BML_VECTOR3_H
