#include "BML/Sphere.h"

Sphere::Sphere()
    : m_center(Vector3()), m_radius(0.0f) {}

Sphere::Sphere(const Vector3& center, float radius)
    : m_center(center), m_radius(radius) {}

Vector3 Sphere::getCenter() const {
    return m_center;
}

float Sphere::getRadius() const {
    return m_radius;
}

void Sphere::setCenter(const Vector3& center) {
    m_center = center;
}

void Sphere::setRadius(float radius) {
    m_radius = radius;
}

bool Sphere::intersects(const Ray& ray, float& t) const {
    const float EPSILON = 0.00001f;

    Vector3 oc = ray.getOrigin() - m_center;
    float a = ray.getDirection() * ray.getDirection();
    float b = 2.0f * (oc * ray.getDirection());
    float c = oc * oc - m_radius * m_radius;
    float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0.0f)
        return false;

    float sqrtDiscriminant = std::sqrt(discriminant);
    float t1 = (-b - sqrtDiscriminant) / (2.0f * a);
    float t2 = (-b + sqrtDiscriminant) / (2.0f * a);

    if (t1 > EPSILON && t1 < t) {
        t = t1;
        return true;
    }

    if (t2 > EPSILON && t2 < t) {
        t = t2;
        return true;
    }

    return false;
}
