#ifndef BML_RAY_H
#define BML_RAY_H

#include <cmath>
#include "BML/Vector3.h"

class Ray {
public:
    // 构造函数
    Ray();
    Ray(const Vector3& origin, const Vector3& direction);
    
    // 获取起点和方向
    Vector3 getOrigin() const;
    Vector3 getDirection() const;

    // 设置起点和方向
    void setOrigin(const Vector3& v);
    void setDirection(const Vector3& v);

    // 获取参数t处的点
    Vector3 pointAt(float t) const;

private:
    Vector3 m_origin, m_direction;
};

#endif // BML_RAY_H
