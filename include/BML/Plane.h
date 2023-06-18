#ifndef BML_PLANE_H
#define BML_PLANE_H

#include <cmath>
#include "BML/Vector3.h"
#include "BML/Line.h"
#include "BML/Ray.h"
#include "BML/LineSegment.h"

class Plane {
public:
    // 构造函数
    Plane();
    Plane(const Vector3& point, const Vector3& normal);
    Plane(float a, float b, float c, float d);

    // 重载运算符
    bool operator==(const Plane& plane) const;
    bool operator!=(const Plane& plane) const;

    // 获取和设置平面参数
    void set(const Vector3& point, const Vector3& normal);
    void set(float a, float b, float c, float d);
    Vector3 getNormal() const;
    void setNormal(const Vector3& normal);
    float getDistance() const;
    void setDistance(float distance);

    // 判断点是否在平面上
    bool contains(const Vector3& point) const;

    // 计算平面和直线、射线、线段之间的交点
    Vector3 intersect(const Line& line) const;
    Vector3 intersect(const Ray& ray) const;
    Vector3 intersect(const LineSegment& line_segment) const;

    // distanceToPoint() 函数返回点到平面的距离
    float distanceToPoint(const Vector3& point) const;

    // normalize() 函数将平面法线归一化
    void normalize();

private:
    Vector3 m_normal;  // 平面法线
    float m_distance;  // 平面到原点的距离
};

#endif  // BML_PLANE_H
