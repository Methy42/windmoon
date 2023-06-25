#include "SML/FrustumPlane.h"

FrustumPlane::FrustumPlane(Vector3 v1, Vector3 v2, Vector3 v3)
{
    // 计算平面法向量
    m_normal = ((v2 - v1) ^ (v3 - v1)).normalize();

    // 计算平面位置
    m_position = v1;
}

double FrustumPlane::distanceToPoint(Vector3 point) const
{
    return m_normal * (point - m_position);
}

Vector3 FrustumPlane::getNormal() const
{
    return m_normal;
}
