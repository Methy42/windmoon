#ifndef INIT_SCENE_H
#define INIT_SCENE_H

#include <thread>
#include "utils/ServerConnect.h"
#include "BML/Material.h"
#include "BML/Color.h"
#include "BML/Light.h"
#include "SML/Scene.h"
#include "SML/PerspectiveCamera.h"
#include "SML/Plane.h"

class InitScene: public Scene
{
private:
    /* data */
public:
    InitScene(/* args */);
};


#endif // INIT_SCENE_H
