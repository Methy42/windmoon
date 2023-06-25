#include "BML/BoundingBox.h"

BoundingBox::BoundingBox()
    : min(Vector3()), max(Vector3()) {}

BoundingBox::BoundingBox(const Vector3& min, const Vector3& max)
    : min(min), max(max) {}

bool BoundingBox::intersects(const BoundingBox& other) const {
    if (max.x < other.min.x || min.x > other.max.x)
        return false;
    if (max.y < other.min.y || min.y > other.max.y)
        return false;
    if (max.z < other.min.z || min.z > other.max.z)
        return false;
    return true;
}

Vector3* BoundingBox::getMinMax(const std::vector<Vector3>& vertices) {
    Vector3* result = new Vector3[2];
    result[0] = Vector3(0, 0, 0);
    result[1] = Vector3(0, 0, 0);
    for (int i = 0; i < vertices.size(); i++) {
        result[0].x = std::min(result[0].x, vertices[i].x);
        result[0].y = std::min(result[0].y, vertices[i].y);
        result[0].z = std::min(result[0].z, vertices[i].z);
        result[1].x = std::max(result[1].x, vertices[i].x);
        result[1].y = std::max(result[1].y, vertices[i].y);
        result[1].z = std::max(result[1].z, vertices[i].z);
    }
    return result;
}