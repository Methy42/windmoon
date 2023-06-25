#ifndef BML_COLOR_H
#define BML_COLOR_H

#include <cmath>
#include <algorithm>
#include <string>
#include <iostream>
#include "BML/Vector3.h"

class Color {
public:
    // 构造函数
    Color();
    Color(float r, float g, float b, float a);

    // 获取颜色分量值
    float getRed() const;
    float getGreen() const;
    float getBlue() const;
    float getAlpha() const;

    // 设置颜色分量值
    void setRed(float r);
    void setGreen(float g);
    void setBlue(float b);
    void setAlpha(float a);

    // 获取颜色的HSV分量值
    float getHue() const;
    float getSaturation() const;
    float getValue() const;

    // 设置颜色的HSV分量值
    void setHue(float h);
    void setSaturation(float s);
    void setValue(float v);

    // 获取颜色的亮度
    float getBrightness() const;

    // 颜色叠加
    Color operator+(const Color& c) const;
    Color& operator+=(const Color& other);
    Color& operator+=(const Vector3& v);

    // 颜色减法
    Color operator-(const Color& other) const;
    Color& operator-=(const Color& other);

    // 颜色乘法
    Color operator*(float s) const;
    Color operator*(const Color& c) const;

    // 颜色除法
    Color operator/(float scalar) const;
    Color& operator/=(float scalar);

    // 判断两个颜色是否相等
    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;

    std::string toString() const;

    static Color lerp(const Color& c1, const Color& c2, float t);

    Color clamp() const;

    // blend 混合两个颜色
    static Color blend(const Color& c1, const Color& c2, float t);

    static const Color WHITE;

private:
    float m_r, m_g, m_b, m_a;
    float m_h, m_s, m_v;
};

#endif // BML_COLOR_H
