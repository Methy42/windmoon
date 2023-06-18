#include "BML/Triangle.h"

Triangle::Triangle()
    : m_v1(Vector3()), m_v2(Vector3()), m_v3(Vector3()) {}

Triangle::Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3)
    : m_v1(v1), m_v2(v2), m_v3(v3) {}

Vector3 Triangle::getVertex1() const {
    return m_v1;
}

Vector3 Triangle::getVertex2() const {
    return m_v2;
}

Vector3 Triangle::getVertex3() const {
    return m_v3;
}

void Triangle::setVertex1(const Vector3& v) {
    m_v1 = v;
}

void Triangle::setVertex2(const Vector3& v) {
    m_v2 = v;
}

void Triangle::setVertex3(const Vector3& v) {
    m_v3 = v;
}

Vector3 Triangle::normal() const {
    return ((m_v2 - m_v1)^(m_v3 - m_v1)).normalize();
}

float Triangle::area() const {
    Vector3 e1 = m_v2 - m_v1;
    Vector3 e2 = m_v3 - m_v1;
    return 0.5f * (e1^e2).length();
}

bool Triangle::intersects(const Ray& ray, float& t) const {
    const float EPSILON = 0.000001f;

    Vector3 edge1 = m_v2 - m_v1;
    Vector3 edge2 = m_v3 - m_v1;
    Vector3 h = ray.getDirection()^edge2;
    float a = edge1*h;

    if (a > -EPSILON && a < EPSILON)
        return false;

    float f = 1.0f / a;
    Vector3 s = ray.getOrigin() - m_v1;
    float u = (s * h) * f;

    if (u < 0.0f || u > 1.0f)
        return false;

    Vector3 q = s^edge1;
    float v = (ray.getDirection() * q) * f;

    if (v < 0.0f || u + v > 1.0f)
        return false;

    t = (edge2 * q) * f;
    return t > EPSILON;
}
