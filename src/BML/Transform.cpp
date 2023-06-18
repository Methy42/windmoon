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
    Matrix4 mat_scale = Matrix4::scale(m_scale.getX(), m_scale.getY(), m_scale.getZ());
    Matrix4 mat_rotate = m_rotation.getMatrix();
    Matrix4 mat_trans = Matrix4::translate(m_position.getX(), m_position.getY(), m_position.getZ());
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
    m_scale.setX(m_scale.getX() * x);
    m_scale.setY(m_scale.getY() * y);
    m_scale.setZ(m_scale.getZ() * z);
}

void Transform::scale(const Vector3& v) {
    m_scale.setX(m_scale.getX() * v.getX());
    m_scale.setY(m_scale.getY() * v.getY());
    m_scale.setZ(m_scale.getZ() * v.getZ());
}

// 旋转
void Transform::rotate(float angle, const Vector3& axis) {
    Quaternion q(angle, axis);
    m_rotation = q * m_rotation;
}

void Transform::rotate(const Vector3& euler_angles) {
    Quaternion q = Quaternion::fromEulerAngles(euler_angles.getX(), euler_angles.getY(), euler_angles.getZ());
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
