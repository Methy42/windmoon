#include "BML/Vector2.h"

const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::UNIT_X(1.0f, 0.0f);
const Vector2 Vector2::UNIT_Y(0.0f, 1.0f);

// 构造函数
Vector2::Vector2(): x(0), y(0) {}

Vector2::Vector2(float x, float y): x(x), y(y) {}

// 拷贝构造函数
Vector2::Vector2(const Vector2& v): x(v.x), y(v.y) {}

// 向量加法
Vector2 Vector2::operator+(const Vector2& v) const {
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator+(float scale) const {
    return Vector2(x + scale, y + scale);
}

Vector2 Vector2::operator-() const {  // 实现前置减号运算符
    return Vector2(-x, -y);
}

// 向量减法
Vector2 Vector2::operator-(const Vector2& v) const {
    return Vector2(x - v.x, y - v.y);
}

// 向量点乘
float Vector2::operator*(const Vector2& v) const {
    return x * v.x + y * v.y;
}

// 向量乘以标量
Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

// 向量除以标量
Vector2 Vector2::operator/(float scalar) const {
    return Vector2(x / scalar, y / scalar);
}

// 向量叉乘
float Vector2::operator^(const Vector2& v) const {
    return x * v.y - y * v.x;
}

Vector2& Vector2::operator+=(const Vector2& v) {
    x += v.x;
    y += v.y;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2& Vector2::operator*=(float scale) {
    x *= scale;
    y *= scale;
    return *this;
}

Vector2& Vector2::operator/=(float scale) {
    x /= scale;
    y /= scale;
    return *this;
}

bool Vector2::operator==(const Vector2& v) const {
    return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2& v) const {
    return x != v.x || y != v.y;
}

float Vector2::dot(const Vector2& v) const {
    return x * v.x + y * v.y;
}

float Vector2::length() const {
    return std::sqrt(x * x + y * y);
}

float Vector2::lengthSquared() const {
    return x * x + y * y;
}

void Vector2::normalize() {
    float len = length();
    if (len > 0.0f) {
        x /= len;
        y /= len;
    }
}

std::string Vector2::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

// Path: src/BML/Vector3.cpp