#include "SML/Sphere.h"

Sphere::Sphere(const Vector3& center, float radius)
    : m_center(center), m_radius(radius)
{
}

void Sphere::setCenter(const Vector3& center)
{
    m_center = center;
}

void Sphere::setRadius(float radius)
{
    m_radius = radius;
}

BoundingBox Sphere::getBoundingBox() const
{
    Vector3 min = m_center - Vector3(m_radius, m_radius, m_radius);
    Vector3 max = m_center + Vector3(m_radius, m_radius, m_radius);
    return BoundingBox(min, max);
}

bool Sphere::containsPoint(const Vector3& point) const
{
    float distanceSq = (point - m_center).lengthSquared();
    return distanceSq <= m_radius * m_radius;
}
