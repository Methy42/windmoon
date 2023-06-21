#include "SML/Object.h"

// 构造函数
Object::Object()
{
    m_transform = nullptr;
    m_material = nullptr;
    m_shape = nullptr;
}

// 析构函数
Object::~Object()
{
    if (m_transform != nullptr)
    {
        delete m_transform;
        m_transform = nullptr;
    }

    if (m_material != nullptr)
    {
        delete m_material;
        m_material = nullptr;
    }

    if (m_shape != nullptr)
    {
        delete m_shape;
        m_shape = nullptr;
    }
}

// 获取物体的位置、缩放和旋转信息
Transform* Object::getTransform() const
{
    return m_transform;
}

Material* Object::getMaterial() const
{
    return m_material;
}

Shape* Object::getShape() const
{
    return m_shape;
}

// 设置物体的位置、缩放和旋转信息
void Object::setTransform(const Transform& transform)
{
    *m_transform = transform;
}

void Object::setMaterial(const Material& material)
{
    *m_material = material;
}

void Object::setShape(const Shape& shape)
{
    *m_shape = shape;
}

// 获取物体的变换矩阵
Matrix4 Object::getTransformMatrix() const
{
    return m_transform->getMatrix();
}

// 获取物体的包围盒（最小和最大顶点）
BoundingBox Object::getBoundingBox() const
{
    return m_shape->getBoundingBox();
}