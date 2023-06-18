#ifndef BML_VECTOR3_H
#define BML_VECTOR3_H

#include <cmath>

class Vector3 {
public:
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

    // 获取向量的x, y, z分量
    float getX() const;
    float getY() const;
    float getZ() const;

    // 设置向量的x, y, z分量
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void set(float x, float y, float z);

    static const Vector3 ZERO; // 静态常量 ZERO

private:
    float m_x, m_y, m_z;
};

#endif // BML_VECTOR3_H
