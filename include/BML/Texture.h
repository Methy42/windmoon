#ifndef BML_TEXTURE_H
#define BML_TEXTURE_H
#include <string>

#include "BML/Color.h"
#include "BML/Matrix4.h"

class Texture {
public:
    // 构造函数
    Texture();
    Texture(int width, int height);
    Texture(const Color* pixels, int width, int height);

    // 从文件加载纹理
    // bool loadFromFile(const std::string& filename);

    // 生成纹理mipmap
    void generateMipmaps();

    // 获取纹理宽度和高度
    int getWidth() const;
    int getHeight() const;

    // 获取和设置像素颜色值
    const Color& getPixel(int x, int y) const;
    void setPixel(int x, int y, const Color& color);

    // 纹理过滤（双线性插值）
    Color sample(float u, float v) const;

    // 多重纹理映射
    static Color blend(const Color& c1, const Color& c2, const Color& mask);

    // 透明纹理
    static Color applyAlpha(const Color& color, float alpha);

    // 纹理坐标变换
    Matrix4 getTransformMatrix() const;
    void setTransformMatrix(const Matrix4& matrix);

private:
    int m_width;        // 纹理宽度
    int m_height;       // 纹理高度
    Color* m_pixels;    // 像素数组
    Matrix4 m_transform_matrix; // 纹理坐标变换矩阵
};

#endif // BML_TEXTURE_H
