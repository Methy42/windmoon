#include "BML/Quaternion.h"

// 构造函数
Quaternion::Quaternion() {
    w = 1;
    x = y = z = 0;
}

Quaternion::Quaternion(float w, float x, float y, float z) {
    w = w;
    x = x;
    y = y;
    z = z;
}

Quaternion::Quaternion(float angle, const Vector3& axis) {
    float half_angle = angle * 0.5f;
    float sin_half_angle = sin(half_angle);
    w = cos(half_angle);
    x = axis.x * sin_half_angle;
    y = axis.y * sin_half_angle;
    z = axis.z * sin_half_angle;
}

// 拷贝构造函数
Quaternion::Quaternion(const Quaternion& q) {
    w = q.w;
    x = q.x;
    y = q.y;
    z = q.z;
}

// 四元数加法
Quaternion Quaternion::operator+(const Quaternion& q) const {
    return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
}

// 四元数减法
Quaternion Quaternion::operator-(const Quaternion& q) const {
    return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
}

// 四元数乘法
Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion(w * q.w - x * q.x - y * q.y - z * q.z,
                      w * q.x + x * q.w + y * q.z - z * q.y,
                      w * q.y - x * q.z + y * q.w + z * q.x,
                      w * q.z + x * q.y - y * q.x + z * q.w);
}

// 四元数标量乘法
Quaternion Quaternion::operator*(float c) const {
    return Quaternion(w * c, x * c, y * c, z * c);
}

// 四元数标量除法
Quaternion Quaternion::operator/(float c) const {
    return Quaternion(w / c, x / c, y / c, z / c);
}

void set(float w, float x, float y, float z) {
    w = w;
    x = x;
    y = y;
    z = z;
}

// 四元数共轭
Quaternion Quaternion::conjugate() const {
    return Quaternion(w, -x, -y, -z);
}

// 四元数模长
float Quaternion::magnitude() const {
    return sqrt(w * w + x * x + y * y + z * z);
}

// 四元数归一化
Quaternion Quaternion::normalize() const {
    float mag = magnitude();
    if (mag == 0)
        return Quaternion();
    return Quaternion(w / mag, x / mag, y / mag, z / mag);
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
    Quaternion vec(0, v.x, v.y, v.z);
    Quaternion conj = conjugate();
    Quaternion result_quat = (*this) * vec * conj;
    return Vector3(result_quat.x, result_quat.y, result_quat.z);
}

Matrix4 Quaternion::getMatrix() const {
    Matrix4 result;

    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float xw = x *w;
    float yy = y * y;
    float yz = y * z;
    float yw = y * w;
    float zz = z * z;
    float zw = z * w;

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