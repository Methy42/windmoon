#include "SML/Scene.h"

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::addObject(Object * object) {
    m_objects.push_back(object);
}

void Scene::removeObject(Object * object) {
    for (size_t i = 0; i < m_objects.size(); ++i) {
        if (m_objects[i] == object) {
            m_objects.erase(m_objects.begin() + i);
            break;
        }
    }
}

std::vector<Object *> & Scene::getObjects() {
    return m_objects;
}

void Scene::addLight(Light * light) {
    m_lights.push_back(light);
}

void Scene::removeLight(Light * light) {
    for (size_t i = 0; i < m_lights.size(); ++i) {
        if (m_lights[i] == light) {
            m_lights.erase(m_lights.begin() + i);
            break;
        }
    }
}

std::vector<Light *> Scene::getLights() const {
    return m_lights;
}

int Scene::addCamera(Camera * camera) {
    m_cameras.push_back(camera);

    if (m_cameras.size() == 1) {
        m_currentCamera = camera;
    }

    return m_cameras.size() - 1;
}

void Scene::removeCamera(Camera * camera) {
    for (size_t i = 0; i < m_cameras.size(); ++i) {
        if (m_cameras[i] == camera) {
            m_cameras.erase(m_cameras.begin() + i);
            break;
        }
    }
}

void Scene::removeCamera(int index) {
    m_cameras.erase(m_cameras.begin() + index);
}

Camera * Scene::getCamera(int index) {
    return m_cameras[index];
}

int Scene::getCameraCount() {
    return m_cameras.size();
}

Camera * Scene::getCurrentCamera() {
    return m_currentCamera;
}

void Scene::setCurrentCamera(int index) {
    m_currentCamera = m_cameras[index];
}

void Scene::flattenObjectTree(std::vector<Object *> & result_objects, std::vector<Object *> flatten_objects) {
    for (Object * flatten_object : flatten_objects) {
        result_objects.push_back(flatten_object);
        Scene::flattenObjectTree(result_objects, flatten_object->children);
    }
}