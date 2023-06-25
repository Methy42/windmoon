#include "scenes/InitScene.h"

InitScene::InitScene(/* args */)
{
    // ServerConnect *connect = ServerConnect::getInstance();
    // connect->run();

    PerspectiveCamera *camera = new PerspectiveCamera(90.0f, 1.0f, 0.1f, 100.0f);
    this->addCamera(camera);

    Light *light = new Light(
        Vector3(10.0f, 10.0f, 5.0f), 
        Vector3(255.0f, 255.0f, 255.0f), 
        1.0f
    );
    this->addLight(light);

    Plane *plane = new Plane();
    Material *material = new Material();

    material->setColor(Color(0.0f, 0.0f, 255.0f, 255.0f));

    Object *object = new Object();
    object->setShape(plane);
    object->setMaterial(material);
    this->addObject(object);

    camera->setPosition(Vector3(0.0f, 0.0f, 10.0f));
    camera->setDirection(Vector3(0.0f, 0.0f, 0.0f));
}