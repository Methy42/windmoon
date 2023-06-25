#ifndef SML_PERSPECTIVE_CAMERA_H
#define SML_PERSPECTIVE_CAMERA_H

#include "SML/Camera.h"
#include "SML/Plane.h"


class PerspectiveCamera : public Camera {
public:
    // 构造函数
    PerspectiveCamera(float fov = 60.0f, float aspect = 1.0f, float near = 0.1f, float far = 1000.0f);

    float fov;     // 视角大小
    float aspect;  // 长宽比
    float near;    // 相机到近裁剪面的距离
    float far;     // 相机到远裁剪面的距离

    // 计算投影矩阵
    Matrix4 getProjectionMatrix() const override;

    // 计算视锥体的六个面
    std::vector<Plane> getFrustumPlanes() const;
    void calculateFrustumPlanes();

    // 判断三角形是否在相机视锥体内
    bool isTriangleInFrustum(const Triangle& triangle) const override;

    // 获取点在相机视锥体内的投影
    Vector3 projectOnPlanes(const Vector3& point) const;

    // 获取三角形在相机视锥体内的投影
    Triangle getTriangleInFrustum(Triangle* triangle) const override;

private:
    // 视锥体的六个面
    Plane frustum_planes[6];
};

#endif  // SML_PERSPECTIVE_CAMERA_H
