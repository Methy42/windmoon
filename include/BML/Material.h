#ifndef BML_MATERIAL_H
#define BML_MATERIAL_H

#include <cmath>

#include "BML/Color.h"
#include "BML/Vector3.h"
#include "BML/Texture.h"

class Material {
public:
    // 构造函数
    Material();
    Material(const Color& color, float ambient, float diffuse, float specular, float shininess);

    // 获取和设置颜色
    const Color& getColor() const;
    void setColor(const Color& color);

    // 获取和设置环境光强度
    float getAmbient() const;
    void setAmbient(float ambient);

    // 获取和设置漫反射强度
    float getDiffuse() const;
    void setDiffuse(float diffuse);

    // 获取和设置镜面反射强度
    float getSpecular() const;
    void setSpecular(float specular);

    // 获取和设置高光指数
    float getShininess() const;
    void setShininess(float shininess);

    // 获取和设置纹理
    const Texture& getTexture() const;
    void setTexture(const Texture& texture);

    // 获取和设置折射率
    float getRefractiveIndex() const;
    void setRefractiveIndex(float refractive_index);

    // 获取和设置能见度/不透明度
    float getOpacity() const;
    void setOpacity(float opacity);

    // 计算漫反射分量
    static Color computeDiffuse(const Color& color, const Vector3& normal, const Vector3& light_dir);

    // 计算镜面反射分量
    static Color computeSpecular(const Color& color, const Vector3& normal, const Vector3& light_dir,
                                 const Vector3& view_dir, float shininess);

private:
    Color m_color;             // 材质颜色
    float m_ambient;           // 环境光强度
    float m_diffuse;           // 漫反射强度
    float m_specular;          // 镜面反射强度
    float m_shininess;         // 高光指数
    Texture m_texture;         // 材质纹理
    float m_refractive_index;  // 折射率
    float m_opacity;           // 能见度/不透明度
};

#endif // BML_MATERIAL_H
