#include "SML/PixelRenderer.h"

PixelRenderer::PixelRenderer() {

}

PixelRenderer::~PixelRenderer() {

}

Color PixelRenderer::getPhongShading(const Vector3& point, const Vector3& normal, const Vector3& view, const Material& material, const Scene& scene) const {
    // 获取光源
    std::vector<Light*> lights = scene.getLights();

    // 计算环境光
    Color ambient = Color(material.getAmbient(), material.getAmbient(), material.getAmbient(), material.getAmbient());

    // 计算漫反射光
    Color diffuse = Color(0, 0, 0, 255);
    for (Light* light: lights) {
        // 计算光线方向
        Vector3 lightDirection = light->getPosition() - point;
        lightDirection.normalize();

        // 计算漫反射光
        float diffuseFactor = std::max(0.0f, normal * lightDirection);
        diffuse += light->getColor() * material.getDiffuse() * diffuseFactor;
    }

    // 计算镜面反射光
    Color specular = Color(0, 0, 0, 255);
    for (Light* light: lights) {
        // 计算光线方向
        Vector3 lightDirection = light->getPosition() - point;
        lightDirection.normalize();

        // 计算反射光线方向
        Vector3 reflectDirection = normal * 2 * (normal * lightDirection) - lightDirection;
        reflectDirection.normalize();

        // 计算镜面反射光
        float specularFactor = std::pow(std::max(0.0f, (reflectDirection * view)), material.getShininess());
        specular += light->getColor() * material.getSpecular() * specularFactor;
    }

    // 计算光照颜色
    Color color = ambient + diffuse + specular;
    color.clamp();

    return color;
}

void PixelRenderer::RendererRender(Scene * scene, int width, int height, ...) const {
    // 获取像素矩阵
    va_list args;
    va_start(args, height);
    Color ** pixelMatrix = va_arg(args, Color**);
    va_end(args);

    // 获取场景中的相机
    Camera* cameras = scene->getCurrentCamera();

    // 获取场景中的物体
    std::vector<Object*> objects;
    Scene::flattenObjectTree(objects, scene->getObjects());

    // 声明三角形列表
    std::vector<TriangleExtend> triangleExtends;

    // 计算相机视锥体
    // 获取相机的位置
    Vector3 cameraPosition = cameras->getPosition();
    // 获取相机的方向
    Vector3 cameraDirection = cameras->getDirection();
    // 获取相机的上方向
    Vector3 cameraUp = cameras->getUp();

    // 将场景中的物体转换为三角形列表
    for (Object* object: objects) {
        if (object->getShape() != nullptr) {
            std::vector<Triangle> triangles = object->getShape()->getTriangles();
            for (Triangle triangle: triangles) {
                triangle.v1 = object->getTransformMatrix().inverse() * triangle.v1;
                triangle.v2 = object->getTransformMatrix().inverse() * triangle.v2;
                triangle.v3 = object->getTransformMatrix().inverse() * triangle.v3;

                // 判断三角形是否在相机视锥体内部
                Camera* cameras = scene->getCurrentCamera();
                if (cameras->isTriangleInFrustum(triangle)) {
                    // 获取三角形的材质
                    Material * material = object->getMaterial();
                    // 将三角形和材质打包
                    TriangleExtend triangleExtend = {&triangle, material};
                    // 将打包后的三角形放入三角形列表中
                    triangleExtends.push_back(triangleExtend);

                    // 获取三角形在相机视锥体内部的投影
                    Triangle triangleInFrustum = cameras->getTriangleInFrustum(triangle);

                    // 获取三角形在相机视锥体内部的投影的边界框
                    Vector3* minMax = BoundingBox::getMinMax(std::vector<Vector3> {
                        triangleInFrustum.v1,
                        triangleInFrustum.v2,
                        triangleInFrustum.v3
                    });
                    BoundingBox *boundingBox = new BoundingBox(minMax[0], minMax[1]);

                    // 获取三角形在相机视锥体内部的投影的边界框的最小点和最大点
                    Vector3 minPoint = boundingBox->min;
                    Vector3 maxPoint = boundingBox->max;

                    // 计算三角形所覆盖的像素范围
                    int minX = std::floor(minPoint.x);
                    int maxX = std::ceil(maxPoint.x);
                    int minY = std::floor(minPoint.y);
                    int maxY = std::ceil(maxPoint.y);

                    // 遍历每个像素，并判断其是否被该三角形所覆盖
                    for (int i = minX; i < maxX; i++) {
                        for (int j = minY; j < maxY; j++) {
                            // 判断当前像素是否在三角形内部
                            Vector3 pixelCenter = Vector3(i + 0.5f, j + 0.5f, 0);
                            if (triangleInFrustum.isPointInside(pixelCenter)) {
                                // 计算像素中心到三角形的距离
                                float distance = triangleInFrustum.getDistanceToPoint(pixelCenter);

                                // 获取像素原始颜色
                                Color* originalColor = pixelMatrix[height - j - 1] + i;

                                // 使用 Phong 基础光照模型计算像素新颜色
                                Color newColor = getPhongShading(pixelCenter, triangleInFrustum.normal(), cameraDirection, *material, *scene);

                                // 将新颜色与原始颜色进行混合
                                *originalColor = originalColor->blend(newColor, triangleExtend.material->getColor(), distance);
                            }
                        }
                    }
                }
            }
        }
    }
}