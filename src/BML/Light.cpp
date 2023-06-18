#include "BML/Light.h"

// 构造函数
Light::Light(const Vector3& position, const Vector3& color, float intensity)
        : m_position(position), m_color(color), m_intensity(intensity) {}

// 计算光源与表面法线之间的夹角余弦值
float Light::getCosAngle(const Vector3& normal) const {
    Vector3 dir = m_position - normal;
    float len = dir.length();
    if (len > 0) {
        dir.normalize();
        return normal * dir;
    } else {
        return 0.0f;
    }
}

// 计算漫反射光照分量
Vector3 Light::getDiffuse(const Vector3& point, const Vector3& normal) const {
    float cosAngle = getCosAngle(normal);
    if (cosAngle > 0) {
        float intensity = m_intensity / (4.0f * std::acos(-1.0f) * pow(point.distanceTo(m_position), 2));
        return m_color * cosAngle * intensity;
    } else {
        return Vector3(0.0f, 0.0f, 0.0f);
    }
}

// 计算镜面反射光照分量
Vector3 Light::getSpecular(const Vector3& point, const Vector3& normal, 
                            const Vector3& viewDir, float shininess) const {
    Vector3 dir = m_position - point;
    float len = dir.length();
    if (len > 0) {
        dir.normalize();
        Vector3 reflDir = normal * (2.0f * (normal * dir)) - dir;
        float cosAngle = reflDir * viewDir;
        if (cosAngle > 0) {
            float intensity = m_intensity / (4.0f * std::acos(-1.0f) * pow(len, 2));
            return m_color * std::pow(cosAngle, shininess) * intensity;
        } else {
            return Vector3(0.0f, 0.0f, 0.0f);
        }
    } else {
        return Vector3(0.0f, 0.0f, 0.0f);
    }
}
