#ifndef SML_RENDERER_H
#define SML_RENDERER_H

#include <vector>
#include <cmath>
#include "SML/Camera.h"
#include "BML/Color.h"
#include "SML/Object.h"
#include "SML/Scene.h"

class Renderer {
public:
    Renderer();
    virtual ~Renderer();

    void render(Scene * scene, unsigned char * pixels, int width, int height);

private:
    Camera * m_currentCamera;
};

#endif /* SML_RENDERER_H */
