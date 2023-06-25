#include "BML/Triangle.h"

Triangle::Triangle()
    : v1(Vector3()), v2(Vector3()), v3(Vector3()) {}

Triangle::Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector2& uv1, const Vector2& uv2, const Vector2& uv3)
    : v1(v1), v2(v2), v3(v3), tv1(uv1), tv2(uv2), tv3(uv3) {}

Vector3 Triangle::normal() const {
    return ((v2 - v1)^(v3 - v1)).normalize();
}

float Triangle::area() const {
    Vector3 e1 = v2 - v1;
    Vector3 e2 = v3 - v1;
    return 0.5f * (e1^e2).length();
}

bool Triangle::intersects(const Ray& ray, float& t) const {
    const float EPSILON = 0.000001f;

    Vector3 edge1 = v2 - v1;
    Vector3 edge2 = v3 - v1;
    Vector3 h = ray.getDirection()^edge2;
    float a = edge1*h;

    if (a > -EPSILON && a < EPSILON)
        return false;

    float f = 1.0f / a;
    Vector3 s = ray.getOrigin() - v1;
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

Vector3 Triangle::getVertex(int index) const {
    switch (index) {
        case 0:
            return v1;
        case 1:
            return v2;
        case 2:
            return v3;
        default:
            return v1;
    }
}

bool Triangle::isPointInside(const Vector3& point) const {
    Vector3 edge1 = v2 - v1;
    Vector3 edge2 = v3 - v1;
    Vector3 edge3 = point - v1;

    float dot11 = edge1 * edge1;
    float dot12 = edge1 * edge2;
    float dot13 = edge1 * edge3;
    float dot22 = edge2 * edge2;
    float dot23 = edge2 * edge3;

    float inverDeno = 1 / (dot11 * dot22 - dot12 * dot12);
    float u = (dot22 * dot13 - dot12 * dot23) * inverDeno;
    if (u < 0 || u > 1)
        return false;

    float v = (dot11 * dot23 - dot12 * dot13) * inverDeno;
    if (v < 0 || v > 1)
        return false;

    return u + v <= 1;
}

float Triangle::getDistanceToPoint(const Vector3& point) const
{
    Vector3 edge1 = v2 - v1;
    Vector3 edge2 = v3 - v1;
    Vector3 edge3 = point - v1;

    float dot11 = edge1 * edge1;
    float dot12 = edge1 * edge2;
    float dot13 = edge1 * edge3;
    float dot22 = edge2 * edge2;
    float dot23 = edge2 * edge3;

    float inverDeno = 1 / (dot11 * dot22 - dot12 * dot12);
    float u = (dot22 * dot13 - dot12 * dot23) * inverDeno;
    if (u < 0 || u > 1)
        return -1;

    float v = (dot11 * dot23 - dot12 * dot13) * inverDeno;
    if (v < 0 || v > 1)
        return -1;

    return (u + v <= 1) ? (edge3 * (edge1^edge2).normalize()) : -1;
}