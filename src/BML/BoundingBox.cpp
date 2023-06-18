#include "BML/BoundingBox.h"

BoundingBox::BoundingBox()
    : m_min(Vector3()), m_max(Vector3()) {}

BoundingBox::BoundingBox(const Vector3& min, const Vector3& max)
    : m_min(min), m_max(max) {}

Vector3 BoundingBox::getMin() const {
    return m_min;
}

Vector3 BoundingBox::getMax() const {
    return m_max;
}

void BoundingBox::setMin(const Vector3& v) {
    m_min = v;
}

void BoundingBox::setMax(const Vector3& v) {
    m_max = v;
}

bool BoundingBox::intersects(const BoundingBox& other) const {
    if (m_max.getX() < other.getMin().getX() || m_min.getX() > other.getMax().getX())
        return false;
    if (m_max.getY() < other.getMin().getY() || m_min.getY() > other.getMax().getY())
        return false;
    if (m_max.getZ() < other.getMin().getZ() || m_min.getZ() > other.getMax().getZ())
        return false;
    return true;
}
