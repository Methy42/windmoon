#include "YouHuang/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(const Vector3& position, const Vector3& target, const Vector3& up) : Camera(position, target, up) {
    m_fov = 45.0f;
}

PerspectiveCamera::~PerspectiveCamera() {}

float PerspectiveCamera::getAspectRatio() const {
    return 1.0f;
}

// getFrameBuffer 怎么实现
unsigned int PerspectiveCamera::getFrameBuffer() const {
    return 0;
}

void PerspectiveCamera::setFov(float fov) {
    m_fov = fov;
}

float PerspectiveCamera::getFov() const {
    return m_fov;
}

// Path: src/YouHuang/Renderer.cpp