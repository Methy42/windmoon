#include "SML/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
    : m_fov(fov), m_aspect(aspect), m_near(near), m_far(far)
{
}

void PerspectiveCamera::setFov(float fov)
{
    m_fov = fov;
}

void PerspectiveCamera::setAspect(float aspect)
{
    m_aspect = aspect;
}

void PerspectiveCamera::setNear(float near)
{
    m_near = near;
}

void PerspectiveCamera::setFar(float far)
{
    m_far = far;
}

Matrix4 PerspectiveCamera::getProjectionMatrix() const
{
    return Matrix4::perspective(m_fov, m_aspect, m_near, m_far);
}
