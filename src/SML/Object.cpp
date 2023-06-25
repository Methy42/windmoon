#include "SML/Object.h"

// 构造函数
Object::Object()
{
    m_transform = new Transform();
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
Object* Object::getParent() const
{
    return m_parent;
}

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
void Object::setParent(Object* parent)
{
    m_parent = parent;
}

void Object::setTransform(const Transform& transform)
{
    *m_transform = transform;
}

void Object::setMaterial(Material* material)
{
    m_material = material;
}

void Object::setShape(Shape* shape)
{
    m_shape = shape;
}

// 获取物体的变换矩阵
Matrix4 Object::getTransformMatrix() const
{
    // 如果物体还有子节点，则需要将子节点的变换矩阵乘到物体的变换矩阵上
    if (m_parent != nullptr)
    {
        return m_parent->getTransformMatrix() * m_transform->getMatrix();
    }
    else
    {
        return m_transform->getMatrix();
    }
}

// 获取物体的包围盒（最小和最大顶点）
BoundingBox Object::getBoundingBox() const
{
    return m_shape->getBoundingBox();
}

void Object::addChild(Object* child)
{
    children.push_back(child);
}