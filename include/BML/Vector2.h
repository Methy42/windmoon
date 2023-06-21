#ifndef BML_VECTOR2_H
#define BML_VECTOR2_H

#include <cmath>
#include <string>

class Vector2 {
public:
    // 构造函数
    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector2& v);

    // 重载运算符
    Vector2 operator+(const Vector2& v) const;
    Vector2 operator+(float scale) const;
    Vector2 operator-(const Vector2& v) const;
    float operator*(const Vector2& v) const;
    Vector2 operator*(float scale) const;
    Vector2 operator/(float scale) const;
    float operator^(const Vector2& v) const;
    Vector2& operator+=(const Vector2& v);
    Vector2& operator-=(const Vector2& v);
    Vector2& operator*=(float scale);
    Vector2& operator/=(float scale);
    Vector2 operator-() const;
    bool operator==(const Vector2& v) const;
    bool operator!=(const Vector2& v) const;

    // 向量点乘
    float dot(const Vector2& v) const;

    // 向量长度
    float length() const;

    // 向量长度的平方
    float lengthSquared() const;

    // 向量归一化
    void normalize();

    // 获取向量的字符串表示
    std::string toString() const;

    // 零向量
    static const Vector2 ZERO;

    // 单位向量
    static const Vector2 UNIT_X;
    static const Vector2 UNIT_Y;

    // 向量坐标
    float x;
    float y;
};

#endif  // BML_VECTOR2_H