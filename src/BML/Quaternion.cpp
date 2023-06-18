#include "BML/Quaternion.h"

// 构造函数
Quaternion::Quaternion() {
    m_w = 1;
    m_x = m_y = m_z = 0;
}

Quaternion::Quaternion(float w, float x, float y, float z) {
    m_w = w;
    m_x = x;
    m_y = y;
    m_z = z;
}

Quaternion::Quaternion(float angle, const Vector3& axis) {
    float half_angle = angle * 0.5f;
    float sin_half_angle = sin(half_angle);
    m_w = cos(half_angle);
    m_x = axis.getX() * sin_half_angle;
    m_y = axis.getY() * sin_half_angle;
    m_z = axis.getZ() * sin_half_angle;
}

// 拷贝构造函数
Quaternion::Quaternion(const Quaternion& q) {
    m_w = q.m_w;
    m_x = q.m_x;
    m_y = q.m_y;
    m_z = q.m_z;
}

// 四元数加法
Quaternion Quaternion::operator+(const Quaternion& q) const {
    return Quaternion(m_w + q.m_w, m_x + q.m_x, m_y + q.m_y, m_z + q.m_z);
}

// 四元数减法
Quaternion Quaternion::operator-(const Quaternion& q) const {
    return Quaternion(m_w - q.m_w, m_x - q.m_x, m_y - q.m_y, m_z - q.m_z);
}

// 四元数乘法
Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion(m_w * q.m_w - m_x * q.m_x - m_y * q.m_y - m_z * q.m_z,
                      m_w * q.m_x + m_x * q.m_w + m_y * q.m_z - m_z * q.m_y,
                      m_w * q.m_y - m_x * q.m_z + m_y * q.m_w + m_z * q.m_x,
                      m_w * q.m_z + m_x * q.m_y - m_y * q.m_x + m_z * q.m_w);
}

// 四元数标量乘法
Quaternion Quaternion::operator*(float c) const {
    return Quaternion(m_w * c, m_x * c, m_y * c, m_z * c);
}

// 四元数标量除法
Quaternion Quaternion::operator/(float c) const {
    return Quaternion(m_w / c, m_x / c, m_y / c, m_z / c);
}

// 获取四元数元素
float Quaternion::getW() const {
    return m_w;
}

float Quaternion::getX() const {
    return m_x;
}

float Quaternion::getY() const {
    return m_y;
}

float Quaternion::getZ() const {
    return m_z;
}

// 设置四元数元素
void Quaternion::setW(float w) {
    m_w = w;
}

void Quaternion::setX(float x) {
    m_x = x;
}

void Quaternion::setY(float y) {
    m_y = y;
}

void Quaternion::setZ(float z) {
    m_z = z;
}

// 四元数共轭
Quaternion Quaternion::conjugate() const {
    return Quaternion(m_w, -m_x, -m_y, -m_z);
}

// 四元数模长
float Quaternion::magnitude() const {
    return sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
}

// 四元数归一化
Quaternion Quaternion::normalize() const {
    float mag = magnitude();
    if (mag == 0)
        return Quaternion();
    return Quaternion(m_w / mag, m_x / mag, m_y / mag, m_z / mag);
}

// 四元数逆
Quaternion Quaternion::inverse() const {
    float mag = magnitude();
    if (mag == 0)
        return Quaternion();
    Quaternion conj = conjugate();
    return conj / mag;
}

// 轴角矢量表示旋转
Quaternion Quaternion::fromAxisAngle(float angle, const Vector3& axis) {
    return Quaternion(angle, axis);
}

// 欧拉角表示旋转
Quaternion Quaternion::fromEulerAngles(float pitch, float yaw, float roll) {
    float cos_pitch = cos(pitch * 0.5f);
    float sin_pitch = sin(pitch * 0.5f);
    float cos_yaw = cos(yaw * 0.5f);
    float sin_yaw = sin(yaw * 0.5f);
    float cos_roll = cos(roll * 0.5f);
    float sin_roll = sin(roll * 0.5f);

    return Quaternion(cos_pitch * cos_yaw * cos_roll + sin_pitch * sin_yaw * sin_roll,
                    sin_pitch * cos_yaw * cos_roll - cos_pitch * sin_yaw * sin_roll,
                    cos_pitch * sin_yaw * cos_roll + sin_pitch * cos_yaw * sin_roll,
                    cos_pitch * cos_yaw * sin_roll - sin_pitch * sin_yaw * cos_roll);
}

// 旋转向量v，返回旋转后的向量
Vector3 Quaternion::rotate(const Vector3& v) const {
    Quaternion vec(0, v.getX(), v.getY(), v.getZ());
    Quaternion conj = conjugate();
    Quaternion result_quat = (*this) * vec * conj;
    return Vector3(result_quat.getX(), result_quat.getY(), result_quat.getZ());
}

Matrix4 Quaternion::getMatrix() const {
    Matrix4 result;

    float xx = m_x * m_x;
    float xy = m_x * m_y;
    float xz = m_x * m_z;
    float xw = m_x *m_w;
    float yy = m_y * m_y;
    float yz = m_y * m_z;
    float yw = m_y * m_w;
    float zz = m_z * m_z;
    float zw = m_z * m_w;

    result.set(0, 0, 1 - 2 * (yy + zz));
    result.set(0, 1, 2 * (xy - zw));
    result.set(0, 2, 2 * (xz + yw));

    result.set(1, 0, 2 * (xy + zw));
    result.set(1, 1, 1 - 2 * (xx + zz));
    result.set(1, 2, 2 * (yz - xw));

    result.set(2, 0, 2 * (xz - yw));
    result.set(2, 1, 2 * (yz + xw));
    result.set(2, 2, 1 - 2 * (xx + yy));

    return result;
}