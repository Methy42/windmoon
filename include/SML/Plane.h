#ifndef SML_PLANE_H
#define SML_PLANE_H

#include <cmath>
#include "BML/Shape.h"
#include "BML/Vector3.h"
#include "BML/Line.h"
#include "BML/Vector2.h"
#include "BML/Ray.h"
#include "BML/LineSegment.h"
#include "BML/BoundingBox.h"
#include "BML/Triangle.h"

class Plane : public Shape {
public:
    Plane(int width = 10, int height = 10, Vector3 normal = {0, 0, 1}, Vector3 position = {0, 0, 0});
    Plane(Vector3 v1, Vector3 v2, Vector3 v3);
    ~Plane();

    // 实现Shape中的获取顶点坐标方法
    std::vector<Vector3> getVertices() const override;

    // 实现Shape中的获取三角形面方法
    std::vector<Triangle> getTriangles() const override;

    // 实现Shape中的获取包围盒方法
    BoundingBox getBoundingBox() const override;

    // 归一化平面法向量
    void normalize();

    // 获取平面法向量
    Vector3 getNormal() const;

    // distanceToPoint方法返回点到平面的距离
    double distanceToPoint(Vector3 point) const;

private:
    int m_width, m_height;
    Vector3 m_normal, m_position;
};

#endif  // SML_PLANE_H
