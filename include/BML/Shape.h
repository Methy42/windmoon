#ifndef BML_SHAPE_H
#define BML_SHAPE_H

#include <cmath>
#include "BML/Vector3.h"   // 三维向量类
#include "BML/Matrix4.h"   // 4x4矩阵类
#include "BML/BoundingBox.h"   // 包围盒类

class Shape {
public:
  Shape();
  virtual ~Shape();

  // computeVertices 用于计算顶点坐标
  virtual void computeVertices() = 0;
  // computeNormals 用于计算顶点法向量
  virtual void computeNormals() = 0;
  // computeTextureCoords 用于计算顶点纹理坐标
  virtual void computeTextureCoords() = 0;

  const Vector3& getPosition() const;
  void setPosition(const Vector3& position);

  const Vector3& getScale() const;
  void setScale(const Vector3& scale);

  const Matrix4& getModelMatrix() const;

  virtual BoundingBox getBoundingBox() const = 0;

protected:
  Vector3 m_position;
  Vector3 m_scale;
  Matrix4 m_modelMatrix; // m_modelMatrix 是模型矩阵
};

#endif  // BML_SHAPE_H