#ifndef BML_TRIANGLE_H
#define BML_TRIANGLE_H

#include <cmath>

#include "BML/Vector3.h"
#include "BML/Ray.h"

class Triangle {
public:
    // 构造函数
    Triangle();
    Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3);
    
    // 获取三个顶点
    Vector3 getVertex1() const;
    Vector3 getVertex2() const;
    Vector3 getVertex3() const;

    // 设置三个顶点
    void setVertex1(const Vector3& v);
    void setVertex2(const Vector3& v);
    void setVertex3(const Vector3& v);

    // 计算法向量
    Vector3 normal() const;

    // 计算面积
    float area() const;

    // 射线与三角形求交
    bool intersects(const Ray& ray, float& t) const;

private:
    Vector3 m_v1, m_v2, m_v3;
};

#endif // BML_TRIANGLE_H
