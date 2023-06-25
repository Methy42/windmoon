#ifndef SML_ORTHOGRAPHIC_CAMERA_H
#define SML_ORTHOGRAPHIC_CAMERA_H

#include "SML/Camera.h"

class OrthographicCamera : public Camera {
public:
    // 构造函数
    OrthographicCamera(float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f, float near = 0.1f, float far = 1000.0f);

    // 设置投影参数
    void setLeft(float left);
    void setRight(float right);
    void setBottom(float bottom);
    void setTop(float top);
    void setNear(float near);
    void setFar(float far);

    // 计算投影矩阵
    Matrix4 getProjectionMatrix() const override;

    // 判断三角形是否在相机视锥体内
    bool isTriangleInFrustum(const Triangle& triangle) const override;

    // 获取三角形在相机视锥体内的投影
    Triangle getTriangleInFrustum(const Triangle& triangle) const override;

private:
    float m_left;    // 左裁剪面
    float m_right;   // 右裁剪面
    float m_bottom;  // 下裁剪面
    float m_top;     // 上裁剪面
    float m_near;    // 近裁剪面
    float m_far;     // 远裁剪面
};

#endif  // SML_ORTHOGRAPHIC_CAMERA_H