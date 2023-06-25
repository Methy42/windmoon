#ifndef BML_TRIANGLE_H
#define BML_TRIANGLE_H

#include <cmath>

#include "BML/Vector3.h"
#include "BML/Vector2.h"
#include "BML/Ray.h"

class Triangle {
public:
    // 构造函数
    Triangle();
    Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector2& tv1, const Vector2& tv2, const Vector2& tv3);

    Vector3 v1, v2, v3;
    Vector2 tv1, tv2, tv3;

    // 计算法向量
    Vector3 normal() const;

    // 计算面积
    float area() const;

    // 射线与三角形求交
    bool intersects(const Ray& ray, float& t) const;

    // 获取顶点坐标
    Vector3 getVertex(int index) const;

    // isPointInside 判断点是否在三角形内部
    bool isPointInside(const Vector3& point) const;

    // getDistanceToPoint 获取点到三角形的距离
    float getDistanceToPoint(const Vector3& point) const;
};

#endif // BML_TRIANGLE_H
