#ifndef BML_BOUNDING_BOX_H
#define BML_BOUNDING_BOX_H

#include <algorithm>
#include <vector>
#include "BML/Vector3.h"

class BoundingBox {
public:
    // 构造函数
    BoundingBox();
    BoundingBox(const Vector3& min, const Vector3& max);

    Vector3 min, max;

    // 碰撞检测
    bool intersects(const BoundingBox& other) const;

    // 从多个顶点中获取最大值和最小值
    static Vector3* getMinMax(const std::vector<Vector3>& vertices);
};

#endif // BML_BOUNDING_BOX_H
