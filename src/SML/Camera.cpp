#include "SML/Camera.h"

Camera::Camera(): m_position(Vector3::ZERO), m_direction(Vector3::UNIT_Z), m_up(Vector3::UNIT_Y) {}

void Camera::setPosition(const Vector3& position) {
    m_position = position;
}

void Camera::setDirection(const Vector3& direction) {
    m_direction = direction.normalize();
    m_up = ((m_direction ^ m_up) ^ m_direction);
}

void Camera::setUp(const Vector3& up) {
    m_up = up.normalize();
    m_direction = ((m_up ^ m_direction) ^ m_up);
}

Matrix4 Camera::getViewMatrix() const
{
    // 将相机方向、上方向和右方向作为坐标系的三个轴向量
    Vector3 zAxis = -m_direction;
    Vector3 xAxis = (m_up ^ zAxis).normalize();
    Vector3 yAxis = zAxis ^ xAxis;

    // 构建旋转矩阵并与平移矩阵相乘
    Matrix4 orientation = Matrix4::identity();
    orientation.setColumn(0, Vector4(xAxis, 0.0f));
    orientation.setColumn(1, Vector4(yAxis, 0.0f));
    orientation.setColumn(2, Vector4(zAxis, 0.0f));
    Matrix4 translate = Matrix4::translate(-m_position);

    // 返回视图矩阵
    return orientation * translate;
}
