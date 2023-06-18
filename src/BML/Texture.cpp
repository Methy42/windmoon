#include "BML/Texture.h"

Texture::Texture()
    : m_width(0), m_height(0), m_pixels(nullptr) {}

Texture::Texture(int width, int height)
    : m_width(width), m_height(height), m_pixels(new Color[width * height]) {}

Texture::Texture(const Color* pixels, int width, int height)
    : m_width(width), m_height(height), m_pixels(new Color[width * height]) {
    for (int i = 0; i < width * height; ++i) {
        m_pixels[i] = pixels[i];
    }
}

// bool Texture::loadFromFile(const std::string& filename) {
//     int width, height, channels;
//     unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
//     if (data == nullptr) {
//         return false;
//     }

//     // 根据通道数创建颜色对象
//     m_width = width;
//     m_height = height;
//     m_pixels = new Color[m_width * m_height];
//     int pixel_size = channels == 4 ? 4 : 3;

//     // 将像素数据转换为颜色对象
//     for (int i = 0; i < m_width * m_height; ++i) {
//         int index = i * pixel_size;
//         float r = static_cast<float>(data[index]) / 255.0f;
//         float g = static_cast<float>(data[index + 1]) / 255.0f;
//         float b = static_cast<float>(data[index + 2]) / 255.0f;
//         float a = channels == 4 ? static_cast<float>(data[index + 3]) / 255.0f : 1.0f;
//         m_pixels[i] = Color(r, g, b, a);
//     }

//     stbi_image_free(data);
//     return true;
// }

void Texture::generateMipmaps() {
    // 使用简单的均值滤波方法生成mipmap
    int level = 1;
    while (m_width > 1 && m_height > 1) {
        int new_width = m_width / 2;
        int new_height = m_height / 2;
        Color* new_pixels = new Color[new_width * new_height];
        for (int y = 0; y < new_height; ++y) {
            for (int x = 0; x < new_width; ++x) {
                Color c1 = getPixel(x * 2, y * 2);
                Color c2 = getPixel(x * 2 + 1, y * 2);
                Color c3 = getPixel(x * 2, y * 2 + 1);
                Color c4 = getPixel(x * 2 + 1,y * 2 + 1);
                Color avg_color = (c1 + c2 + c3 + c4) / 4.0f;
                new_pixels[y * new_width + x] = avg_color;
            }
        }
        delete[] m_pixels;
        m_pixels = new_pixels;
        m_width = new_width;
        m_height = new_height;
        ++level;
    }
}

int Texture::getWidth() const {
    return m_width;
}

int Texture::getHeight() const {
    return m_height;
}

const Color& Texture::getPixel(int x, int y) const {
    return m_pixels[y * m_width + x];
}

void Texture::setPixel(int x, int y, const Color& color) {
    m_pixels[y * m_width + x] = color;
}

Color Texture::sample(float u, float v) const {
    // 双线性插值算法
    float x = (m_width - 1) * u;
    float y = (m_height - 1) * v;
    int x1 = static_cast<int>(x);
    int y1 = static_cast<int>(y);
    int x2 = std::min(x1 + 1, m_width - 1);
    int y2 = std::min(y1 + 1, m_height - 1);
    float tx = x - x1;
    float ty = y - y1;
    Color c1 = getPixel(x1, y1);
    Color c2 = getPixel(x2, y1);
    Color c3 = getPixel(x1, y2);
    Color c4 = getPixel(x2, y2);
    Color top = Color::lerp(c1, c2, tx);
    Color bottom = Color::lerp(c3, c4, tx);
    return Color::lerp(top, bottom, ty);
}

Color Texture::blend(const Color& c1, const Color& c2, const Color& mask) {
    // 使用掩码混合两个颜色
    float r = Color::lerp(c1, c2, mask.getRed()).getRed();
    float g = Color::lerp(c1, c2, mask.getGreen()).getGreen();
    float b = Color::lerp(c1, c2, mask.getBlue()).getBlue();
    float a = Color::lerp(c1, c2, mask.getAlpha()).getAlpha();
    
    return Color(r, g, b, a);
}

Color Texture::applyAlpha(const Color& color, float alpha) {
    // 应用透明度到颜色值上
    float r = color.getRed();
    float g = color.getGreen();
    float b = color.getBlue();
    return Color(r, g, b, alpha);
}

Matrix4 Texture::getTransformMatrix() const {
    return m_transform_matrix;
}

void Texture::setTransformMatrix(const Matrix4& matrix) {
    m_transform_matrix = matrix;
}
