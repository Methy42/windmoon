#include "SML/Plane.h"

Plane::Plane(float width, float height)
{
    this->v1 = {-width / 2, 0, -height / 2};
    this->v2 = {width / 2, 0, -height / 2};
    this->v3 = {-width / 2, 0, height / 2};
    this->v4 = {width / 2, 0, height / 2};
}

Plane::Plane(Vector3 v1, Vector3 v2, Vector3 v3)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->v4 = v3 + (v2 - v1);
}

Plane::~Plane()
{
}

std::vector<Vector3> Plane::getVertices() const
{
    std::vector<Vector3> vertices;
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    return vertices;
}

std::vector<Triangle> Plane::getTriangles() const
{
    std::vector<Triangle> triangles;

    Vector3 topLeft = v1;
    Vector3 topRight = v2;
    Vector3 bottomLeft = v3;
    Vector3 bottomRight = v4;

    // 计算纹理顶点坐标
    Vector2 texTopLeft = {0, 0};
    Vector2 texTopRight = {1, 0};
    Vector2 texBottomLeft = {0, 1};
    Vector2 texBottomRight = {1, 1};

    std::cout << "topLeft: (" << topLeft.x << ", " << topLeft.y << ", " << topLeft.z << ")" << std::endl;
    std::cout << "topRight: (" << topRight.x << ", " << topRight.y << ", " << topRight.z << ")" << std::endl;
    std::cout << "bottomLeft: (" << bottomLeft.x << ", " << bottomLeft.y << ", " << bottomLeft.z << ")" << std::endl;
    std::cout << "bottomRight: (" << bottomRight.x << ", " << bottomRight.y << ", " << bottomRight.z << ")" << std::endl;

    triangles.push_back(Triangle(topLeft, topRight, bottomLeft, texTopLeft, texTopRight, texBottomLeft));
    triangles.push_back(Triangle(bottomLeft, topRight, bottomRight, texBottomLeft, texTopRight, texBottomRight));
    return triangles;
}

BoundingBox Plane::getBoundingBox() const
{
    // 计算顶点坐标x、y、z的最大值和最小值
    std::vector<Vector3> vertices = getVertices();
    Vector3 * minMax = BoundingBox::getMinMax(vertices);

    // 返回包围盒
    return BoundingBox(minMax[0], minMax[1]);
}

double Plane::distanceToPoint(Vector3 point) const
{
    // 计算平面法向量
    Vector3 normal = (v2 - v1 ^ v3 - v1).normalize();

    // 计算平面方程
    double a = normal.x;
    double b = normal.y;
    double c = normal.z;
    double d = -(a * v1.x + b * v1.y + c * v1.z);

    // 计算点到平面的距离
    return std::abs(a * point.x + b * point.y + c * point.z + d) / std::sqrt(a * a + b * b + c * c);
}