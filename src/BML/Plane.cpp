#include "BML/Plane.h"

Plane::Plane() : m_normal(0, 1, 0), m_distance(0) {}

Plane::Plane(const Vector3& point, const Vector3& normal)
    : m_normal(normal.normalize()), m_distance(-m_normal * point) {}

Plane::Plane(float a, float b, float c, float d)
    : m_normal(a, b, c), m_distance(d / sqrt(a * a + b * b + c * c)) {
    m_normal.normalize();
}

bool Plane::operator==(const Plane& plane) const {
    return (m_normal == plane.m_normal && fabs(m_distance - plane.m_distance) < 0.001f);
}

bool Plane::operator!=(const Plane& plane) const {
    return !(*this == plane);
}

void Plane::set(const Vector3& point, const Vector3& normal) {
    m_normal = normal.normalize();
    m_distance = -m_normal * point;
}

void Plane::set(float a, float b, float c, float d) {
    m_normal.set(a, b, c);
    m_distance = d / sqrt(a * a + b * b + c * c);
    m_normal.normalize();
}

Vector3 Plane::getNormal() const {
    return m_normal;
}

void Plane::setNormal(const Vector3& normal) {
    m_normal = normal.normalize();
}

float Plane::getDistance() const {
    return m_distance;
}

void Plane::setDistance(float distance) {
    m_distance = distance;
}

bool Plane::contains(const Vector3& point) const {
    return (fabs(m_normal * point + m_distance) < 0.001f);
}

Vector3 Plane::intersect(const Line& line) const {
    Vector3 direction = line.direction().normalize();
    float t = -(m_normal * line.getOrigin() + m_distance) / (m_normal * direction);
    return line.getOrigin() + direction * t;
}

Vector3 Plane::intersect(const Ray& ray) const {
    Vector3 direction = ray.getDirection().normalize();
    float t = -(m_normal * ray.getOrigin() + m_distance) / (m_normal * direction);
    if (t >= 0) {
        return ray.getOrigin() + direction * t;
    } else {
        return Vector3::ZERO;
    }
}

Vector3 Plane::intersect(const LineSegment& line_segment) const {
    Vector3 direction = line_segment.getDirection().normalize();
    float t = -(m_normal * line_segment.getStart() + m_distance) / (m_normal * direction);
    if (t >= 0 && t <= line_segment.getLength()) {
        return line_segment.getStart() + direction * t;
    } else {
        return Vector3::ZERO;
    }
}

float Plane::distanceToPoint(const Vector3& point) const {
    return fabs(m_normal * point + m_distance);
}

// normalize() 函数将平面法线归一化
void Plane::normalize() {
    m_normal.normalize();
}