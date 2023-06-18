#ifndef BML_LINE_SEGMENT_H
#define BML_LINE_SEGMENT_H

#include <cmath>
#include "BML/Vector3.h"

class LineSegment {
public:
    // 构造函数
    LineSegment();
    LineSegment(const Vector3& start, const Vector3& end);

    // 获取和设置线段的起点和终点
    void set(const Vector3& start, const Vector3& end);
    Vector3 getStart() const;
    Vector3 getEnd() const;

    // 获取线段的长度和方向
    float getLength() const;
    Vector3 getDirection() const;

private:
    Vector3 m_start;  // 起点
    Vector3 m_end;  // 终点
};

#endif  // BML_LINE_SEGMENT_H
