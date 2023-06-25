#ifndef SML_SCENE_H
#define SML_SCENE_H

#include <vector>
#include "BML/Light.h"
#include "SML/Object.h"
#include "SML/Camera.h"

class Scene {
public:
    Scene();
    virtual ~Scene();

    void addObject(Object * object);
    void removeObject(Object * object);
    std::vector<Object *> & getObjects();

    void addLight(Light * light);
    void removeLight(Light * light);
    std::vector<Light *> getLights() const;

    int addCamera(Camera * camera);
    void removeCamera(Camera * camera);
    void removeCamera(int index);
    Camera * getCamera(int index);
    int getCameraCount();
    Camera * getCurrentCamera();
    void setCurrentCamera(int index);

    // 拉平物体树，将所有物体放到一个数组中
    static void flattenObjectTree(std::vector<Object *> & objects, std::vector<Object *> flatten_objects);

private:
    std::vector<Object *> m_objects;
    std::vector<Light *> m_lights;
    std::vector<Camera *> m_cameras;
    Camera * m_currentCamera;
};

#endif  // SML_SCENE_H