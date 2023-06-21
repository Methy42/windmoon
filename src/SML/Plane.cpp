#include "SML/Plane.h"

Plane::Plane(float width, float height)
    : Shape(), m_width(width), m_height(height) {}

void Plane::computeVertices() {
  float halfWidth = m_width * 0.5f;
  float halfHeight = m_height * 0.5f;
  Vector3 vertices[] = {
      {halfWidth, 0.0f, halfHeight},
      {halfWidth, 0.0f, -halfHeight},
      {-halfWidth, 0.0f, -halfHeight},
      {-halfWidth, 0.0f, halfHeight},
  };
  // 计算模型矩阵
  m_modelMatrix = Matrix4::translate(m_position) * Matrix4::scale(m_scale);
  // 在模型矩阵下计算顶点坐标
  for (int i = 0; i < 4; i++) {
    m_vertices[i] = m_modelMatrix * vertices[i];
  }
}

void Plane::computeNormals() {
  Vector3 normal = (m_vertices[1] - m_vertices[0]) ^ (m_vertices[2] - m_vertices[0]);
  m_normal = normal.normalize();
}

void Plane::computeTextureCoords() {
  float hw = m_width / 2.0f;
  float hh = m_height / 2.0f;
  Vector2 texcoords[] = {{1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}};
  for (int i = 0; i < 4; i++) {
    m_texcoords[i] = Vector2(texcoords[i].x * m_width, texcoords[i].y * m_height);
  }

  // 线性插值计算其它顶点的纹理坐标
  float distanceX = m_vertices[1].getX() - m_vertices[0].getX();
  float distanceZ = m_vertices[3].getZ() - m_vertices[0].getZ();

  Vector2 texCoord0 = m_texcoords[3] + Vector2(distanceX / m_width, distanceZ / m_height) * (m_texcoords[0] - m_texcoords[3]);
  Vector2 texCoord1 = m_texcoords[2] + Vector2(distanceX / m_width, distanceZ / m_height) * (m_texcoords[1] - m_texcoords[2]);

  m_texcoords[0] = texCoord0;
  m_texcoords[1] = texCoord1;
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

// 通过三个点来定义平面, d 是平面方程的常量项，表示平面到原点的距离
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