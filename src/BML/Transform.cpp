#include "BML/Transform.h"

// 构造函数
Transform::Transform() {
    m_position = Vector3(0, 0, 0);
    m_scale = Vector3(1, 1, 1);
    m_rotation = Quaternion();
}

// 拷贝构造函数
Transform::Transform(const Transform& t) {
    m_position = t.m_position;
    m_scale = t.m_scale;
    m_rotation = t.m_rotation;
}

// 获取变换矩阵
Matrix4 Transform::getMatrix() const {
    Matrix4 mat_scale = Matrix4::scale(m_scale.x, m_scale.y, m_scale.z);
    Matrix4 mat_rotate = m_rotation.getMatrix();
    Matrix4 mat_trans = Matrix4::translate(m_position.x, m_position.y, m_position.z);
    return mat_trans * mat_rotate * mat_scale;
}

// 平移
void Transform::translate(float x, float y, float z) {
    m_position += Vector3(x, y, z);
}

void Transform::translate(const Vector3& v) {
    m_position += v;
}

// 缩放
void Transform::scale(float x, float y, float z) {
    m_scale.x = m_scale.x * x;
    m_scale.y = m_scale.y * y;
    m_scale.z = m_scale.z * z;
}

void Transform::scale(const Vector3& v) {
    m_scale.x = m_scale.x * v.x;
    m_scale.y = m_scale.y * v.y;
    m_scale.z = m_scale.z * v.z;
}

// 旋转
void Transform::rotate(float angle, const Vector3& axis) {
    Quaternion q(angle, axis);
    m_rotation = q * m_rotation;
}

void Transform::rotate(const Vector3& euler_angles) {
    Quaternion q = Quaternion::fromEulerAngles(euler_angles.x, euler_angles.y, euler_angles.z);
    m_rotation = q * m_rotation;
}

void Transform::rotate(const Quaternion& q) {
    m_rotation = q * m_rotation;
}

// 设置位置、缩放和旋转
void Transform::setPosition(const Vector3& pos) {
    m_position = pos;
}

void Transform::setScale(const Vector3& scale) {
    m_scale = scale;
}

void Transform::setRotation(const Quaternion& rot) {
    m_rotation = rot;
}

// 获取位置、缩放和旋转
Vector3 Transform::getPosition() const {
    return m_position;
}

Vector3 Transform::getScale() const {
    return m_scale;
}

Quaternion Transform::getRotation() const {
    return m_rotation;
}
