#include "BML/Camera.h"

Camera::Camera(const Vector3& position, const Vector3& target, const Vector3& up)
    : m_position(position), m_direction((target - position).normalize()), m_up(up.normalize()),
      m_minFovLimit(10.0f), m_maxFovLimit(90.0f) {}

void Camera::setPosition(const Vector3& position) {
    m_position = position;
}

Vector3 Camera::getPosition() const {
    return m_position;
}

void Camera::setDirection(const Vector3& direction) {
    m_direction = direction.normalize();
}

Vector3 Camera::getDirection() const {
    return m_direction;
}

void Camera::setUp(const Vector3& up) {
    m_up = up.normalize();
}

Vector3 Camera::getUp() const {
    return m_up;
}

Matrix4 Camera::getViewMatrix() const {
    Vector3 center = m_position + m_direction;
    return Matrix4::lookAt(m_position, center, m_up);
}

Matrix4 Camera::getProjectionMatrix(float aspectRatio) const {
    return Matrix4::perspective(60.0f, aspectRatio, 0.1f, 1000.0f);
}

Matrix4 Camera::getPerspectiveMatrix(float fov, float nearPlane, float farPlane) const {
    // getAspectRatio()方法是一个虚方法，由子类实现
    return Matrix4::perspective(fov, getAspectRatio(), nearPlane, farPlane);
}

Matrix4 Camera::getOrthographicMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane) const {
    return Matrix4::orthographic(left, right, bottom, top, nearPlane, farPlane);
}

std::vector<Plane> Camera::getFrustumPlanes(const Matrix4& viewProjMatrix) const {
    std::vector<Plane> planes(6);
    calculateFrustumPlanes(viewProjMatrix, planes);
    return planes;
}

void Camera::setFovLimits(float minFov, float maxFov) {
    m_minFovLimit = minFov;
    m_maxFovLimit = maxFov;
}

float Camera::getMinFovLimit() const {
    return m_minFovLimit;
}

float Camera::getMaxFovLimit() const {
    return m_maxFovLimit;
}

bool Camera::collidesWithSphere(const Sphere& sphere) const {
    // 计算视锥体的裁剪平面
    Matrix4 viewProjMatrix = getViewMatrix() * getPerspectiveMatrix(60.0f, 0.1f, 1000.0f);
    std::vector<Plane> planes = getFrustumPlanes(viewProjMatrix);

    // 对于每个裁剪平面，检测是否与球体相交
    for (const auto& plane : planes) {
        if (plane.distanceToPoint(sphere.getCenter()) < -sphere.getRadius()) {
            // 裁剪平面和球体没有相交
            return false;
        }
    }

    return true;
}

// BoundingBox 并不是一个球体，没有 getCenter() 和 getRadius() 方法
bool Camera::collidesWithBox(const BoundingBox& box) const {
    // 计算视锥体的裁剪平面
    Matrix4 viewProjMatrix = getViewMatrix() * getPerspectiveMatrix(60.0f, 0.1f, 1000.0f);
    std::vector<Plane> planes = getFrustumPlanes(viewProjMatrix);

    // 对于每个裁剪平面，检测是否与包围盒相交
    for (const auto& plane : planes) {
        Vector3 normal = plane.getNormal();
        Vector3 min = box.getMin();
        Vector3 max = box.getMax();
        Vector3 p = Vector3(min.getX(), min.getY(), min.getZ());
        if (normal.getX() >= 0.0f) {
            p.setX(max.getX());
        }
        if (normal.getY() >= 0.0f) {
            p.setY(max.getY());
        }
        if (normal.getZ() >= 0.0f) {
            p.setZ(max.getZ());
        }
        if (plane.distanceToPoint(p) < 0.0f) {
            // 裁剪平面和包围盒没有相交
            return false;
        }
    }

    return true;
}

// 计算裁剪平面的辅助方法
void Camera::calculateFrustumPlanes(const Matrix4& viewProjMatrix, std::vector<Plane>& planes) const {
    // 右裁剪平面
    planes[0].setNormal(Vector3(viewProjMatrix.get(3, 0) - viewProjMatrix.get(0, 0),
                                 viewProjMatrix.get(3, 1) - viewProjMatrix.get(0, 1),
                                 viewProjMatrix.get(3, 2) - viewProjMatrix.get(0, 2)));
    planes[0].setDistance(viewProjMatrix.get(3, 3) - viewProjMatrix.get(0, 3));

    // 左裁剪平面
    planes[1].setNormal(Vector3(viewProjMatrix.get(3, 0) + viewProjMatrix.get(0, 0),
                                 viewProjMatrix.get(3, 1) + viewProjMatrix.get(0, 1),
                                 viewProjMatrix.get(3, 2) + viewProjMatrix.get(0, 2)));
    planes[1].setDistance(viewProjMatrix.get(3, 3) + viewProjMatrix.get(0, 3));

    // 上裁剪平面
    planes[2].setNormal(Vector3(viewProjMatrix.get(3, 0) - viewProjMatrix.get(1, 0),
                                 viewProjMatrix.get(3, 1) - viewProjMatrix.get(1, 1),
                                 viewProjMatrix.get(3, 2) - viewProjMatrix.get(1, 2)));
    planes[2].setDistance(viewProjMatrix.get(3, 3) - viewProjMatrix.get(1, 3));

    // 下裁剪平面
    planes[3].setNormal(Vector3(viewProjMatrix.get(3, 0) + viewProjMatrix.get(1, 0),
                                 viewProjMatrix.get(3, 1) + viewProjMatrix.get(1, 1),
                                 viewProjMatrix.get(3, 2) + viewProjMatrix.get(1, 2)));
    planes[3].setDistance(viewProjMatrix.get(3, 3) + viewProjMatrix.get(1, 3));

    // 远裁剪平面
    planes[4].setNormal(Vector3(viewProjMatrix.get(3, 0) - viewProjMatrix.get(2, 0),
                                 viewProjMatrix.get(3, 1) - viewProjMatrix.get(2, 1),
                                 viewProjMatrix.get(3, 2) - viewProjMatrix.get(2, 2)));
    planes[4].setDistance(viewProjMatrix.get(3, 3) - viewProjMatrix.get(2, 3));

    // 近裁剪平面
    planes[5].setNormal(Vector3(viewProjMatrix.get(3, 0) + viewProjMatrix.get(2, 0),
                                 viewProjMatrix.get(3, 1) + viewProjMatrix.get(2, 1),
                                 viewProjMatrix.get(3, 2) + viewProjMatrix.get(2, 2)));
    planes[5].setDistance(viewProjMatrix.get(3, 3) + viewProjMatrix.get(2, 3));
    
    // 归一化裁剪平面
    for (auto& plane : planes) {
        plane.normalize();
    }
}
