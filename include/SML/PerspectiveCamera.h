#ifndef SML_PERSPECTIVE_CAMERA_H
#define SML_PERSPECTIVE_CAMERA_H

#include "SML/Camera.h"

class PerspectiveCamera : public Camera {
public:
    // 构造函数
    PerspectiveCamera(float fov = 60.0f, float aspect = 1.0f, float near = 0.1f, float far = 1000.0f);

    // 设置投影参数
    void setFov(float fov);
    void setAspect(float aspect);
    void setNear(float near);
    void setFar(float far);

    // 计算投影矩阵
    Matrix4 getProjectionMatrix() const override;

private:
    float m_fov;     // 视角大小
    float m_aspect;  // 长宽比
    float m_near;    // 近裁剪面
    float m_far;     // 远裁剪面
};

#endif  // SML_PERSPECTIVE_CAMERA_H
