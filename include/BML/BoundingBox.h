#ifndef BML_BOUNDING_BOX_H
#define BML_BOUNDING_BOX_H

#include <algorithm>
#include "BML/Vector3.h"

class BoundingBox {
public:
    // 构造函数
    BoundingBox();
    BoundingBox(const Vector3& min, const Vector3& max);
    
    // 获取最小值和最大值
    Vector3 getMin() const;
    Vector3 getMax() const;

    // 设置最小值和最大值
    void setMin(const Vector3& v);
    void setMax(const Vector3& v);

    // 碰撞检测
    bool intersects(const BoundingBox& other) const;

private:
    Vector3 m_min, m_max;
};

#endif // BML_BOUNDING_BOX_H
