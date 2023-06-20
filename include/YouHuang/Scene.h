#ifndef YOUHUANG_SCENE_H
#define YOUHUANG_SCENE_H

#include <vector>
#include "YouHuang/Object.h"
#include "BML/Camera.h"

class Scene {
public:
    Scene();
    virtual ~Scene();

    void addObject(Object * object);
    void removeObject(Object * object);

    std::vector<Object *> & getObjects();

    int addCamera(Camera * camera);
    void removeCamera(Camera * camera);
    void removeCamera(int index);
    Camera * getCamera(int index);
    int getCameraCount();
    Camera * getCurrentCamera();
    void setCurrentCamera(int index);

private:
    std::vector<Object *> m_objects;
    std::vector<Camera *> m_cameras;
    Camera * m_currentCamera;
};

#endif  // YOUHUANG_SCENE_H