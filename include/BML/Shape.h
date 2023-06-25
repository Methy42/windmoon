#ifndef BML_SHAPE_H
#define BML_SHAPE_H

#include <cmath>
#include <vector>
#include "BML/Vector3.h"   // 三维向量类
#include "BML/Matrix4.h"   // 4x4矩阵类
#include "BML/BoundingBox.h"   // 包围盒类
#include "BML/Triangle.h"

class Shape {
public:
  Shape();
  virtual ~Shape();

  // 获取顶点坐标
  virtual std::vector<Vector3> getVertices() const = 0;
  // 获取三角形面
  virtual std::vector<Triangle> getTriangles() const = 0;

  virtual BoundingBox getBoundingBox() const = 0;
};

#endif  // BML_SHAPE_H