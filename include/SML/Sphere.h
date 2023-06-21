#ifndef SML_SPHERE_H
#define SML_SPHERE_H

#include "BML/Vector3.h"
#include "BML/BoundingBox.h"
#include "BML/Shape.h"

class Sphere : public Shape {
public:
    // 构造函数
    Sphere(const Vector3& center = Vector3(), float radius = 1.0f);

    // 获取球心位置和半径
    Vector3 getCenter() const { return m_center; }
    float getRadius() const { return m_radius; }

    // 设置球心位置和半径
    void setCenter(const Vector3& center);
    void setRadius(float radius);

    // 计算球体的包围盒
    BoundingBox getBoundingBox() const override;

    // 判断点是否在球体内
    bool containsPoint(const Vector3& point) const;

private:
    Vector3 m_center;   // 球心位置
    float m_radius;     // 球体半径
};

#endif  // SML_SPHERE_H
