#ifndef BML_CAMERA_H
#define BML_CAMERA_H

#include <vector>
#include "BML/Vector3.h"
#include "BML/Matrix4.h"
#include "BML/Plane.h"
#include "BML/Sphere.h"
#include "BML/BoundingBox.h"

class Camera {
public:
    // 构造函数
    Camera(const Vector3& position, const Vector3& target, const Vector3& up);

    // 获取和设置摄像机位置、朝向和上向量
    void setPosition(const Vector3& position);
    Vector3 getPosition() const;
    void setDirection(const Vector3& direction);
    Vector3 getDirection() const;
    void setUp(const Vector3& up);
    Vector3 getUp() const;

    // 计算视矩阵
    Matrix4 getViewMatrix() const;

    // 计算投影矩阵
    Matrix4 getProjectionMatrix(float aspectRatio) const;
    Matrix4 getPerspectiveMatrix(float fov, float nearPlane, float farPlane) const;
    Matrix4 getOrthographicMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane) const;

    // 计算裁剪平面
    std::vector<Plane> getFrustumPlanes(const Matrix4& viewProjMatrix) const;

    // 设置FOV限制
    void setFovLimits(float minFov, float maxFov);
    float getMinFovLimit() const;
    float getMaxFovLimit() const;

    // 处理碰撞检测
    bool collidesWithSphere(const Sphere& sphere) const;
    bool collidesWithBox(const BoundingBox& box) const;

    // getAspectRatio()方法是一个虚方法，由子类实现
    virtual float getAspectRatio() const = 0;

    // getFrameBuffer 的方法是一个虚方法，由子类实现
    virtual unsigned int getFrameBuffer() const = 0;

private:
    Vector3 m_position;           // 摄像机位置
    Vector3 m_direction;          // 摄像机朝向
    Vector3 m_up;                 // 摄像机上向量
    float m_minFovLimit;          // FOV最小限制
    float m_maxFovLimit;          // FOV最大限制

    // 计算裁剪平面的辅助方法
    void calculateFrustumPlanes(const Matrix4& viewProjMatrix, std::vector<Plane>& planes) const;
};

#endif // BML_CAMERA_H