#include "SML/OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
    : m_left(left), m_right(right), m_bottom(bottom), m_top(top), m_near(near), m_far(far)
{
}

void OrthographicCamera::setLeft(float left)
{
    m_left = left;
}

void OrthographicCamera::setRight(float right)
{
    m_right = right;
}

void OrthographicCamera::setBottom(float bottom)
{
    m_bottom = bottom;
}

void OrthographicCamera::setTop(float top)
{
    m_top = top;
}

void OrthographicCamera::setNear(float near)
{
    m_near = near;
}

void OrthographicCamera::setFar(float far)
{
    m_far = far;
}

Matrix4 OrthographicCamera::getProjectionMatrix() const
{
    return Matrix4::orthographic(m_left, m_right, m_bottom, m_top, m_near, m_far);
}