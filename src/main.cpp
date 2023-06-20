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

        // 放弃 CPU 时间片，允许其他线程或进程运行
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}