#include "scenes/InitScene.h"

InitScene::InitScene(/* args */)
{
    ServerConnect *connect = ServerConnect::getInstance();
    connect->run();
}