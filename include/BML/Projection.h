#ifndef BML_PROJECTION_H
#define BML_PROJECTION_H

#include <cmath>
#include "BML/Matrix4.h"

class Projection {
public:
    // 正射投影
    static Matrix4 orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    
    // 透视投影
    static Matrix4 perspective(float fovY, float aspectRatio, float nearPlane, float farPlane);
};

#endif // BML_PROJECTION_H
