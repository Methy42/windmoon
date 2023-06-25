#ifndef BML_TRANSFORM_H
#define BML_TRANSFORM_H

#include <iostream>
#include "BML/Vector3.h"
#include "BML/Matrix4.h"
#include "BML/Quaternion.h"

class Transform {
public:
    // 构造函数
    Transform();
    // 拷贝构造函数
    Transform(const Transform& t);

    // 获取变换矩阵
    Matrix4 getMatrix() const;

    // 平移
    void translate(float x, float y, float z);
    void translate(const Vector3& v);
    // 缩放
    void scale(float x, float y, float z);
    void scale(const Vector3& v);
    // 旋转
    void rotate(float angle, const Vector3& axis);
    void rotate(const Vector3& euler_angles);
    void rotate(const Quaternion& q);
    // 设置位置、缩放和旋转
    void setPosition(const Vector3& pos);
    void setScale(const Vector3& scale);
    void setRotation(const Quaternion& rot);

    // 获取位置、缩放和旋转
    Vector3 getPosition() const;
    Vector3 getScale() const;
    Quaternion getRotation() const;

private:
    Vector3 m_position;     // 位置
    Vector3 m_scale;        // 缩放
    Quaternion m_rotation;  // 旋转
};

#endif // BML_TRANSFORM_H
