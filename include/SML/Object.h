#ifndef SML_OBJECT_H
#define SML_OBJECT_H

#include <cmath>
#include <string>
#include <vector>
#include <memory>
#include "BML/Transform.h" // 变换类
#include "BML/Shape.h"     // 形状类
#include "BML/Material.h"  // 材质类
#include "BML/Vector3.h"   // 三维向量类
#include "BML/Matrix4.h"   // 4x4矩阵类
#include "BML/BoundingBox.h"   // 包围盒类
#include "SML/Composite.h"

class Object : public Composite
{
public:
    // 构造函数
    Object();
    ~Object();

    // 获取物体的位置、缩放和旋转信息
    Transform* getTransform() const;
    Material* getMaterial() const;
    Shape* getShape() const;

    // 设置物体的位置、缩放和旋转信息
    void setTransform(const Transform& position);
    void setMaterial(const Material& scale);
    void setShape(const Shape& rotation);

    // 获取物体的变换矩阵
    Matrix4 getTransformMatrix() const;

    // 获取物体的包围盒（最小和最大顶点）
    BoundingBox getBoundingBox() const;

private:
    Transform* m_transform;            // 变换组件
    Material* m_material;              // 材质组件
    Shape* m_shape;   // 形状组件

    std::vector<std::shared_ptr<Composite>> m_children;   // 子节点列表
};

#endif  // SML_OBJECT3D_H
