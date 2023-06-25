#ifndef SML_PLANE_H
#define SML_PLANE_H

#include <cmath>
#include <iostream>
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
    Plane(float width = 10, float height = 10);
    Plane(Vector3 v1, Vector3 v2, Vector3 v3);
    ~Plane();

    Vector3 v1, v2, v3, v4;

    // 实现Shape中的获取顶点坐标方法
    std::vector<Vector3> getVertices() const override;

    // 实现Shape中的获取三角形面方法
    std::vector<Triangle> getTriangles() const override;

    // 实现Shape中的获取包围盒方法
    BoundingBox getBoundingBox() const override;

    // distanceToPoint方法返回点到平面的距离
    double distanceToPoint(Vector3 point) const;
};

#endif  // SML_PLANE_H
