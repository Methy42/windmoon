#include "BML/Vector3.h"

const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_X(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_Y(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_Z(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::UNIT_SCALE(1.0f, 1.0f, 1.0f);

// 构造函数
Vector3::Vector3(): m_x(0), m_y(0), m_z(0) {}

Vector3::Vector3(float x, float y, float z): m_x(x), m_y(y), m_z(z) {}

// 拷贝构造函数
Vector3::Vector3(const Vector3& v): m_x(v.m_x), m_y(v.m_y), m_z(v.m_z) {}

// 向量加法
Vector3 Vector3::operator+(const Vector3& v) const {
    return Vector3(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
}

Vector3 Vector3::operator-() const {  // 实现前置减号运算符
    return Vector3(-m_x, -m_y, -m_z);
}

// 向量减法
Vector3 Vector3::operator-(const Vector3& v) const {
    return Vector3(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z);
}

// 向量点乘
float Vector3::operator*(const Vector3& v) const {
    return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z;
}

// 向量乘以标量
Vector3 Vector3::operator*(float scalar) const {
    return Vector3(m_x * scalar, m_y * scalar, m_z * scalar);
}

// 向量除以标量
Vector3 Vector3::operator/(float scalar) const {
    return Vector3(m_x / scalar, m_y / scalar, m_z / scalar);
}

// 向量叉乘
Vector3 Vector3::operator^(const Vector3& v) const {
    float x = m_y * v.m_z - m_z * v.m_y;
    float y = m_z * v.m_x - m_x * v.m_z;
    float z = m_x * v.m_y - m_y * v.m_x;
    return Vector3(x, y, z);
}

Vector3& Vector3::operator+=(const Vector3& v) {
    m_x += v.getX();
    m_y += v.getY();
    m_z += v.getZ();

    return *this;
}

bool Vector3::operator==(const Vector3& v) const {
    return (m_x == v.m_x && m_y == v.m_y && m_z == v.m_z);
}

// 向量标准化
Vector3 Vector3::normalize() const {
    float len = length();
    if (len == 0)
        return Vector3();
    else
        return Vector3(m_x / len, m_y / len, m_z / len);
}

// 向量长度
float Vector3::length() const {
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
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
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

// 获取向量的x, y, z分量
float Vector3::getX() const {
    return m_x;
}

float Vector3::getY() const {
    return m_y;
}

float Vector3::getZ() const {
    return m_z;
}

// 设置向量的x, y, z分量
void Vector3::setX(float x) {
    m_x = x;
}

void Vector3::setY(float y) {
    m_y = y;
}

void Vector3::setZ(float z) {
    m_z = z;
}

void Vector3::set(float x, float y, float z) {
    m_x = x;
    m_y = y;
    m_z = z;
}
