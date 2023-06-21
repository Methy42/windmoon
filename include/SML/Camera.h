#ifndef SML_CAMERA_H
#define SML_CAMERA_H

#include "BML/Vector3.h"   // 三维向量类
#include "BML/Vector4.h"   // 四维向量类
#include "BML/Matrix4.h"   // 4x4矩阵类

class Camera {
public:
    // 构造函数
    Camera();

    // 获取相机的位置、朝向和上方向
    Vector3 getPosition() const { return m_position; }
    Vector3 getDirection() const { return m_direction; }
    Vector3 getUp() const { return m_up; }

    // 设置相机的位置、朝向和上方向
    void setPosition(const Vector3& position);
    void setDirection(const Vector3& direction);
    void setUp(const Vector3& up);

    // 计算视图矩阵
    Matrix4 getViewMatrix() const;

    // 计算投影矩阵
    virtual Matrix4 getProjectionMatrix() const = 0;

protected:
    Vector3 m_position;     // 相机位置
    Vector3 m_direction;    // 相机朝向
    Vector3 m_up;           // 相机上方向
};

#endif  // SML_CAMERA_H
