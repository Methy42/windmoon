#ifndef BML_LINE_H
#define BML_LINE_H

#include <cmath>
#include "BML/Vector3.h"

class Line {
public:
    // 构造函数
    Line();
    Line(const Vector3& start, const Vector3& end);
    
    // 获取起点和终点
    Vector3 getStart() const;
    Vector3 getEnd() const;

    // 设置起点和终点
    void setStart(const Vector3& v);
    void setEnd(const Vector3& v);

    // 获取长度
    float length() const;

    // 获取方向向量
    Vector3 direction() const;

    // 获取中点
    Vector3 midpoint() const;

    // 获取参数t处的点
    Vector3 pointAt(float t) const;

    // 返回起点
    Vector3 getOrigin() const;

private:
    Vector3 m_start, m_end;
};

#endif // BML_LINE_H
