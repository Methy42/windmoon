#include "BML/Shape.h"

Shape::Shape()
    : m_position(Vector3::ZERO), m_scale(Vector3::UNIT_SCALE), m_modelMatrix(Matrix4::identity())
{
}

Shape::~Shape()
{
}

const Vector3& Shape::getPosition() const { return m_position; }

void Shape::setPosition(const Vector3& position)
{
    m_position = position;
    m_modelMatrix = Matrix4::translate(m_position) * Matrix4::scale(m_scale);
}

const Vector3& Shape::getScale() const { return m_scale; }

void Shape::setScale(const Vector3& scale)
{
    m_scale = scale;
    m_modelMatrix = Matrix4::translate(m_position) * Matrix4::scale(m_scale);
}

const Matrix4& Shape::getModelMatrix() const { return m_modelMatrix; }