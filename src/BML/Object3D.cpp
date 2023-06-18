#include "BML/Object3D.h"

// 构造函数
Object3D::Object3D()
    : m_position(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f), m_rotation(0.0f, 0.0f, 0.0f) {}

// 设置物体的位置
void Object3D::setPosition(const Vector3& position) {
    m_position = position;
}

// 设置物体的缩放
void Object3D::setScale(const Vector3& scale) {
    m_scale = scale;
}

// 设置物体的旋转
void Object3D::setRotation(const Vector3& rotation) {
    m_rotation = rotation;
}

// 获取物体的变换矩阵
Matrix4 Object3D::getTransformMatrix() const {
    // 计算旋转矩阵
    Matrix4 rotX = Matrix4::rotateX(m_rotation.getX());
    Matrix4 rotY = Matrix4::rotateY(m_rotation.getY());
    Matrix4 rotZ = Matrix4::rotateZ(m_rotation.getZ());
    Matrix4 rot = rotZ * rotY * rotX;

    // 计算缩放矩阵和位移矩阵
    Matrix4 scl = Matrix4::scale(m_scale);
    Matrix4 pos = Matrix4::translate(m_position);

    // 计算最终变换矩阵
    return pos * rot * scl;
}

// 获取物体的包围盒（最小和最大顶点）
BoundingBox Object3D::getBoundingBox() const {
    // 顶点坐标
    Vector3 v[8] = {
        Vector3(-0.5f, -0.5f, -0.5f),
        Vector3(0.5f, -0.5f, -0.5f),
        Vector3(-0.5f, 0.5f, -0.5f),
        Vector3(0.5f, 0.5f, -0.5f),
        Vector3(-0.5f, -0.5f, 0.5f),
        Vector3(0.5f, -0.5f, 0.5f),
        Vector3(-0.5f, 0.5f, 0.5f),
        Vector3(0.5f, 0.5f, 0.5f)
    };

    // 计算旋转矩阵
    Matrix4 rotX = Matrix4::rotateX(m_rotation.getX());
    Matrix4 rotY = Matrix4::rotateY(m_rotation.getY());
    Matrix4 rotZ = Matrix4::rotateZ(m_rotation.getZ());
    Matrix4 rot = rotZ * rotY * rotX;

    // 计算缩放矩阵和位移矩阵
    Matrix4 scl = Matrix4::scale(m_scale);
    Matrix4 pos = Matrix4::translate(m_position);

    // 计算最终变换矩阵
    Matrix4 mat = pos * rot * scl;

    // 计算包围盒
    Vector3 min = mat * v[0];
    Vector3 max = min;
    for (int i = 1; i < 8; ++i) {
        Vector3 p = mat * v[i];
        if (p.getX() < min.getX()) min.setX(p.getX());
        if (p.getY() < min.getY()) min.setY(p.getY());
        if (p.getZ() < min.getZ()) min.setZ(p.getZ());

        if (p.getX() > max.getX()) max.setX(p.getX());
        if (p.getY() > max.getY()) max.setY(p.getY());
        if (p.getZ() > max.getZ()) max.setZ(p.getZ());
    }

    // 构造 BoundingBox 对象并返回
    return BoundingBox(min, max);
}
