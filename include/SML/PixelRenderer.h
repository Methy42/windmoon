#ifndef SML_PIXEL_RENDERER_H
#define SML_PIXEL_RENDERER_H

#include <vector>
#include <cmath>
#include "SML/Camera.h"
#include "BML/Color.h"
#include "BML/Triangle.h"
#include "BML/BoundingBox.h"
#include "SML/Object.h"
#include "SML/Scene.h"
#include "SML/Composite.h"
#include "SML/Renderer.h"

struct TriangleExtend {
    Triangle *triangle;
    Material *material;
};

class PixelRenderer: Renderer {
public:
    PixelRenderer();
    ~PixelRenderer();

    // getPhongShading 获取Phong光照模型的颜色
    Color getPhongShading(const Vector3& point, const Vector3& normal, const Vector3& view, const Material& material, const Scene& scene) const;

    /**
     * @brief 渲染场景
     * @param { Scene * } scene 场景
     * @param { int } width 渲染宽度
     * @param { int } height 渲染高度
     * @param { Color** } pixelMatrix 像素矩阵
     * 需要注意的是，这里的像素矩阵是一个二维数组，行数是height，列数是width
    */
    void RendererRender(Scene * scene, int width, int height, ...) const override;

private:

};

#endif /* SML_PIXEL_RENDERER_H */