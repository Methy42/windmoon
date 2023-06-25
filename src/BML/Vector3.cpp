#include "BML/Vector3.h"

const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_X(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_Y(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_Z(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::UNIT_SCALE(1.0f, 1.0f, 1.0f);

// 构造函数
Vector3::Vector3(): x(0), y(0), z(0) {}

Vector3::Vector3(float x, float y, float z): x(x), y(y), z(z) {}

// 拷贝构造函数
Vector3::Vector3(const Vector3& v): x(v.x), y(v.y), z(v.z) {}

// 向量加法
Vector3 Vector3::operator+(const Vector3& v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-() const {  // 实现前置减号运算符
    return Vector3(-x, -y, -z);
}

// 向量减法
Vector3 Vector3::operator-(const Vector3& v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

// 向量点乘
float Vector3::operator*(const Vector3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

// 向量乘以标量
Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

// 向量除以标量
Vector3 Vector3::operator/(float scalar) const {
    return Vector3(x / scalar, y / scalar, z / scalar);
}

// 向量叉乘
Vector3 Vector3::operator^(const Vector3& v) const {
    float x = y * v.z - z * v.y;
    float y = z * v.x - x * v.z;
    float z = x * v.y - y * v.x;
    return Vector3(x, y, z);
}

Vector3& Vector3::operator+=(const Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

bool Vector3::operator==(const Vector3& v) const {
    return (x == v.x && y == v.y && z == v.z);
}

// 向量标准化
Vector3 Vector3::normalize() const {
    float len = length();
    if (len == 0)
        return Vector3();
    else
        return Vector3(x / len, y / len, z / len);
}

// 向量长度
float Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// reflect函数 用于计算反射向量
Vector3 Vector3::reflect(const Vector3& normal) const {
    return *this - normal * (2 * (*this * normal));
}

float Vector3::distanceTo(const Vector3& other) const {
    return (*this - other).length();
}

// lengthSquared 函数 用于计算向量长度的平方
float Vector3::lengthSquared() const {
    return x * x + y * y + z * z;
}

void Vector3::set(float x, float y, float z) {
    x = x;
    y = y;
    z = z;
}
