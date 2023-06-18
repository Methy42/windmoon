#include "BML/Projection.h"

Matrix4 Projection::orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    float tz = -(farPlane + nearPlane) / (farPlane - nearPlane);

    Matrix4 result;
    result.set(0, 0, 2.0f / (right - left));
    result.set(1, 1, 2.0f / (top - bottom));
    result.set(2, 2, -2.0f / (farPlane - nearPlane));
    result.set(3, 0, tx);
    result.set(3, 1, ty);
    result.set(3, 2, tz);
    result.set(3, 3, 1.0f);

    return result;
}

Matrix4 Projection::perspective(float fovY, float aspectRatio, float nearPlane, float farPlane) {
    float theta = fovY * 0.5f;
    float d = 1.0f / std::tan(theta);

    float A = -(farPlane + nearPlane) / (farPlane - nearPlane);
    float B = (-2.0f * farPlane * nearPlane) / (farPlane - nearPlane);

    Matrix4 result;
    result.set(0, 0, d / aspectRatio);
    result.set(1, 1, d);
    result.set(2, 2, A);
    result.set(2, 3, -1.0f);
    result.set(3, 2, B);

    return result;
}
