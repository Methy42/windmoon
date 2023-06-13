#include <iostream>
#include "scenes/InitScene.h"

int main () {
    std::cout << "Hello, world!" << std::endl;
    InitScene initScene;

    initScene.start();

    bool condition = false;

    while (true) {
        // do something
        if (condition) {
            break;
        }
    }
    return 0;
}