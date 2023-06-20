#ifndef YOUHUANG_PERSPECTIVE_CAMERA_H
#define YOUHUANG_PERSPECTIVE_CAMERA_H

#include "BML/Camera.h"

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(const Vector3& position, const Vector3& target, const Vector3& up);
    virtual ~PerspectiveCamera();

    virtual float getAspectRatio() const;
    unsigned int getFrameBuffer() const;

    void setFov(float fov);
    float getFov() const;

private:
    float m_fov;
};

#endif  // YOUHUANG_PERSPECTIVE_CAMERA_H