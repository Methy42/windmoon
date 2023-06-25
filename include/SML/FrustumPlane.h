#ifndef SML_FRUSTUMPLANE_H
#define SML_FRUSTUMPLANE_H

#include "BML/Vector3.h"

class FrustumPlane {
public:
    FrustumPlane() = default;
    FrustumPlane(Vector3 v1, Vector3 v2, Vector3 v3);

    // 计算到点的距离
    double distanceToPoint(Vector3 point) const;

    // 获取法向量
    Vector3 getNormal() const;

private:
    Vector3 m_normal;  // 平面法向量
    Vector3 m_position;  // 平面位置
};

#endif  // SML_FRUSTUMPLANE_H
