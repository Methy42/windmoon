#ifndef BML_SPHERE_H
#define BML_SPHERE_H

#include <cmath>
#include "BML/Vector3.h"
#include "BML/Ray.h"

class Sphere {
public:
    // 构造函数
    Sphere();
    Sphere(const Vector3& center, float radius);

    // 获取球心和半径
    Vector3 getCenter() const;
    float getRadius() const;

    // 设置球心和半径
    void setCenter(const Vector3& center);
    void setRadius(float radius);

    // 射线与球体求交
    bool intersects(const Ray& ray, float& t) const;

private:
    Vector3 m_center;
    float m_radius;
};

#endif // BML_SPHERE_H
