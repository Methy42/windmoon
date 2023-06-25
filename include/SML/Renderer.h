#ifndef SML_RENDERER_H
#define SML_RENDERER_H

#include <vector>
#include <cmath>
#include "SML/Camera.h"
#include "BML/Color.h"
#include "SML/Object.h"
#include "SML/Scene.h"
#include "SML/Composite.h"

class Renderer {
public:
    Renderer();
    virtual ~Renderer();

    virtual void RendererRender(Scene * scene, int width, int height, ...) const = 0;

private:
    Camera * m_currentCamera;
};

#endif /* SML_RENDERER_H */
