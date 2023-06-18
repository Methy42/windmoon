#ifndef BML_OBJECT3D_H
#define BML_OBJECT3D_H

#include <cmath>
#include "BML/Vector3.h"   // 三维向量类
#include "BML/Matrix4.h"   // 4x4矩阵类
#include "BML/BoundingBox.h"   // 包围盒类

class Object3D {
public:
    // 构造函数
    Object3D();

    // 获取物体的位置、缩放和旋转信息
    Vector3 getPosition() const { return m_position; }
    Vector3 getScale() const { return m_scale; }
    Vector3 getRotation() const { return m_rotation; }

    // 设置物体的位置、缩放和旋转信息
    void setPosition(const Vector3& position);
    void setScale(const Vector3& scale);
    void setRotation(const Vector3& rotation);

    // 获取物体的变换矩阵
    Matrix4 getTransformMatrix() const;

    // 获取物体的包围盒（最小和最大顶点）
    BoundingBox getBoundingBox() const;

private:
    Vector3 m_position;   // 物体位置
    Vector3 m_scale;      // 物体缩放
    Vector3 m_rotation;   // 物体旋转
};

#endif  // BML_OBJECT3D_H
