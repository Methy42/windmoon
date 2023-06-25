#ifndef BML_QUATERNION_H
#define BML_QUATERNION_H

#include <cmath>
#include "BML/Vector3.h"
#include "BML/Matrix4.h"

class Quaternion {
public:
    // 构造函数
    Quaternion();
    Quaternion(float w, float x, float y, float z);
    Quaternion(float angle, const Vector3& axis);
    // 拷贝构造函数
    Quaternion(const Quaternion& q);

    float w, x, y, z;

    // 四元数加法
    Quaternion operator+(const Quaternion& q) const;
    // 四元数减法
    Quaternion operator-(const Quaternion& q) const;
    // 四元数乘法
    Quaternion operator*(const Quaternion& q) const;

    // 四元数标量乘法
    Quaternion operator*(float c) const;
    // 四元数标量除法
    Quaternion operator/(float c) const;
    // 判断四元数相等
    bool operator==(const Quaternion& q) const;

    void set(float w, float x, float y, float z);

    // 四元数共轭
    Quaternion conjugate() const;
    // 四元数模长
    float magnitude() const;
    // 四元数归一化
    Quaternion normalize() const;
    // 四元数逆
    Quaternion inverse() const;

    // 轴角矢量表示旋转
    static Quaternion fromAxisAngle(float angle, const Vector3& axis);
    // 欧拉角表示旋转
    static Quaternion fromEulerAngles(float pitch, float yaw, float roll);

    // 旋转向量v，返回旋转后的向量
    Vector3 rotate(const Vector3& v) const;

    Matrix4 getMatrix() const;
};

#endif // BML_QUATERNION_H
