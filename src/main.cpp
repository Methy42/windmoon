#include <iostream>
#include <fstream>
#include <unistd.h>
#include "BML/Color.h"
#include "SML/PixelRenderer.h"
#include "scenes/InitScene.h"

int main () {
    Logger::getInstance()->setLogLevel(static_cast<Logger::LogLevel>(ClientConfig::getInstance()->getContext()->client_log_level));
    Logger::getInstance()->info("Client start");

    PixelRenderer *renderer = new PixelRenderer();
    InitScene *initScene = new InitScene();
    Color **pixelMatrix = new Color*[100];
    for (int i = 0; i < 100; i++) {
        pixelMatrix[i] = new Color[100];
    }

    renderer->RendererRender(initScene, 100, 100, pixelMatrix);
    std::ofstream outFile("./test.txt");
    if (!outFile.is_open()) {
        std::cout << "Error: failed to open file." << std::endl;
        return 0;
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; ++j) {
            outFile << pixelMatrix[i][j].toString() << ", ";
        }
        outFile << std::endl;
    }

    outFile.close();

    for (int i = 0; i < 100; i++) {
        delete[] pixelMatrix[i];
    }

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