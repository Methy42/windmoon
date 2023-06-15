#include "scenes/InitScene.h"

InitScene::InitScene(/* args */)
{
}

int InitScene::start()
{
    ServerConnect *connect = ServerConnect::getInstance();
    if (connect->run() != 1)
    {
        std::cerr << "Failed to connect to server." << std::endl;
    }

    return 0;
}