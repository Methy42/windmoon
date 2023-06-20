#ifndef INIT_SCENE_H
#define INIT_SCENE_H

#include <thread>
#include "utils/ServerConnect.h"
#include "YouHuang/Scene.h"

class InitScene: Scene
{
private:
    /* data */
public:
    InitScene(/* args */);

    int start();
};


#endif // INIT_SCENE_H
