#include "YouHuang/Renderer.h"

Renderer::Renderer() {
    m_currentCamera = nullptr;
}

Renderer::~Renderer() {

}

void Renderer::render(Scene * scene, unsigned char * pixels, int width, int height) {
    // Get the current camera
    m_currentCamera = scene->getCurrentCamera();

    // Set up the projection matrix
    // ...

    // Set up the view matrix
    // ...

    // Render all objects in the scene
    std::vector<Object *> & objects = scene->getObjects();
    for (size_t i = 0; i < objects.size(); ++i) {
        Object * object = objects[i];

        // Set the model matrix
        // ...

        // Render the object
        // ...

        // Restore the model matrix
        // ...
    }

    // Read back the rendered image from the frame buffer and store it in the output image
    // for (int y = 0; y < height; ++y) {
    //     for (int x = 0; x < width; ++x) {
    //         int index = ((height - y - 1) * width + x) * 4;
    //         Color color = m_currentCamera->getFrameBuffer()->getPixel(x, y);
    //         // Get the pixel color from the frame buffer
    //         // ...

    //         // Set the output image pixel
    //         pixels[index] = r;
    //         pixels[index + 1] = g;
    //         pixels[index + 2] = b;
    //         pixels[index + 3] = a;
    //     }
    // }
}
