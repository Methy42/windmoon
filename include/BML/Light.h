#ifndef BML_LIGHT_H
#define BML_LIGHT_H

#include <cmath>
#include "BML/Vector3.h"  // 向量类

class Light {
public:
    // 构造函数
    Light(const Vector3& position, const Vector3& color, float intensity);

    // 计算光源与表面法线之间的夹角余弦值
    float getCosAngle(const Vector3& normal) const;

    // 计算漫反射光照分量
    Vector3 getDiffuse(const Vector3& point, const Vector3& normal) const;

    // 计算镜面反射光照分量
    Vector3 getSpecular(const Vector3& point, const Vector3& normal, 
                        const Vector3& viewDir, float shininess) const;

    // 获取光源位置
    Vector3 getPosition() const { return m_position; }

    // 获取光源颜色
    Vector3 getColor() const { return m_color; }

    // 获取光源强度
    float getIntensity() const { return m_intensity; }

private:
    Vector3 m_position;   // 光源位置
    Vector3 m_color;      // 光源颜色
    float m_intensity;    // 光源强度
};

#endif  // BML_LIGHT_H
