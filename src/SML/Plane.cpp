#include "SML/Plane.h"

Plane::Plane(int width, int height, Vector3 normal, Vector3 up, Vector3 position)
    : m_width(width), m_height(height), m_normal(normal), m_up(up), m_position(position)
{
}

Plane::Plane(Vector3 v1, Vector3 v2, Vector3 v3)
{
    Vector3 v12 = v2 - v1;
    Vector3 v13 = v3 - v1;
    m_normal = v12 ^ v13;
    m_normal.normalize();
    m_position = v1;
    m_width = 10;
    m_height = 10;
}

Plane::~Plane()
{
}

std::vector<Vector3> Plane::getVertices() const
{
    std::vector<Vector3> vertices;
    // right是法线normal在平面上的一个垂直向量
    Vector3 right = m_normal ^ Vector3(0, 1, 0);
    Vector3 up = right ^ m_normal;
    std::cout << "m_normal: " << m_normal.toString() << std::endl;
    std::cout << "right: " << right.toString() << std::endl;
    std::cout << "up: " << up.toString() << std::endl;
    right.normalize();
    up.normalize();
    Vector3 left = -right;
    Vector3 down = -up;
    Vector3 topLeft = m_position + left * m_width / 2 + up * m_height / 2;
    Vector3 topRight = m_position + right * m_width / 2 + up * m_height / 2;
    Vector3 bottomLeft = m_position + left * m_width / 2 + down * m_height / 2;
    Vector3 bottomRight = m_position + right * m_width / 2 + down * m_height / 2;
    vertices.push_back(topLeft);
    vertices.push_back(topRight);
    vertices.push_back(bottomLeft);
    vertices.push_back(bottomRight);
    return vertices;
}

std::vector<Triangle> Plane::getTriangles() const
{
    std::vector<Triangle> triangles;

    std::vector<Vector3> vertices = getVertices();

    Vector3 topLeft = vertices[0];
    Vector3 topRight = vertices[1];
    Vector3 bottomLeft = vertices[2];
    Vector3 bottomRight = vertices[3];

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

void Plane::normalize()
{
    m_normal.normalize();
}

Vector3 Plane::getNormal() const
{
    return m_normal;
}

double Plane::distanceToPoint(Vector3 point) const
{
    return (point - m_position) * m_normal;
}