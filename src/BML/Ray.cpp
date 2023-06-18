#include "BML/Ray.h"

Ray::Ray()
    : m_origin(Vector3()), m_direction(Vector3()) {}

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : m_origin(origin), m_direction(direction.normalize()) {}

Vector3 Ray::getOrigin() const {
    return m_origin;
}

Vector3 Ray::getDirection() const {
    return m_direction;
}

void Ray::setOrigin(const Vector3& v) {
    m_origin = v;
}

void Ray::setDirection(const Vector3& v) {
    m_direction = v.normalize();
}

Vector3 Ray::pointAt(float t) const {
    return m_origin + m_direction * t;
}
