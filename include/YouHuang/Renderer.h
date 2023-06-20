#ifndef YOUHUANG_RENDERER_H
#define YOUHUANG_RENDERER_H

#include <vector>
#include <cmath>
#include "BML/Camera.h"
#include "BML/Color.h"
#include "YouHuang/Object.h"
#include "YouHuang/Scene.h"

class Renderer {
public:
    Renderer();
    virtual ~Renderer();

    void render(Scene * scene, unsigned char * pixels, int width, int height);

private:
    Camera * m_currentCamera;
};

#endif /* YOUHUANG_RENDERER_H */
