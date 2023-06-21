#include "BML/Vector4.h"

const Vector4 Vector4::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::UNIT_W(0.0f, 0.0f, 0.0f, 1.0f);

// 构造函数
Vector4::Vector4(): x(0), y(0), z(0), w(0) {}
Vector4::Vector4(float x, float y, float z, float w): x(x), y(y), z(z), w(z) {}
Vector4::Vector4(const Vector4& v): x(v.x), y(v.y), z(v.z), w(v.w) {}
Vector4::Vector4(const Vector3& v, float w): x(v.getX()), y(v.getY()), z(v.getZ()), w(w) {}

// 向量加法
Vector4 Vector4::operator+(const Vector4& v) const {
    return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 Vector4::operator-() const {  // 实现前置减号运算符
    return Vector4(-x, -y, -z, -w);
}

// 向量减法
Vector4 Vector4::operator-(const Vector4& v) const {
    return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

// 向量点乘
float Vector4::operator*(const Vector4& v) const {
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

// 向量乘以标量
Vector4 Vector4::operator*(float scalar) const {
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

// 向量除以标量
Vector4 Vector4::operator/(float scalar) const {
    return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

// 向量叉乘
Vector4 Vector4::operator^(const Vector4& v) const {
    float x = y * v.z - z * v.y;
    float y = z * v.x - x * v.z;
    float z = x * v.y - y * v.x;
    return Vector4(x, y, z, 0.0f);
}

Vector4& Vector4::operator+=(const Vector4& v) {
    x += v.getX();
    y += v.getY();
    z += v.getZ();
    w += v.getW();

    return *this;
}

// 比较两个向量是否相等
bool Vector4::operator==(const Vector4& v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

// 向量标准化
Vector4 Vector4::normalize() const {
    float len = length();
    if (len == 0.0f) {
        return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    return Vector4(x / len, y / len, z / len, w / len);
}

// 向量长度
float Vector4::length() const {
    return std::sqrtf(x * x + y * y + z * z + w * w);
}

// 向量长度的平方
float Vector4::lengthSquared() const {
    return x * x + y * y + z * z + w * w;
}

// 获取向量的x, y, z, w分量
float Vector4::getX() const {
    return x;
}

float Vector4::getY() const {
    return y;
}

float Vector4::getZ() const {
    return z;
}

float Vector4::getW() const {
    return w;
}

// 设置向量的x, y, z, w分量
void Vector4::setX(float x) {
    this->x = x;
}

void Vector4::setY(float y) {
    this->y = y;
}

void Vector4::setZ(float z) {
    this->z = z;
}

void Vector4::setW(float w) {
    this->w = w;
}

void Vector4::set(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
