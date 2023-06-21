#ifndef SML_PLANE_H
#define SML_PLANE_H

#include <cmath>
#include "BML/Shape.h"
#include "BML/Vector3.h"
#include "BML/Line.h"
#include "BML/Vector2.h"
#include "BML/Ray.h"
#include "BML/LineSegment.h"

class Plane : public Shape {
public:
    // 构造函数
    Plane(float width, float height);
    virtual ~Plane() {}

    void set(const Vector3& point, const Vector3& normal);
    void set(float a, float b, float c, float d);

    Vector3 getNormal() const;
    void setNormal(const Vector3& normal);
    float getDistance() const;
    void setDistance(float distance);

    virtual void computeVertices() override;
    virtual void computeNormals() override;
    virtual void computeTextureCoords() override;

    // 重载运算符
    bool operator==(const Plane& plane) const;
    bool operator!=(const Plane& plane) const;

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
    float m_width;
    float m_height;
    Vector3 m_vertices[4]; // 平面的四个顶点
    Vector3 m_normal;  // 平面法线
    float m_distance;  // 平面到原点的距离
    Vector2 m_texcoords[4]; // 平面的纹理坐标
};

#endif  // SML_PLANE_H
