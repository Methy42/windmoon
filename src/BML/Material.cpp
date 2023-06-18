#include "BML/Material.h"

Material::Material()
    : m_color(Color::WHITE), m_ambient(0.1f), m_diffuse(0.9f), m_specular(0.9f), m_shininess(16.0f),
      m_refractive_index(1.0f), m_opacity(1.0f) {}

Material::Material(const Color& color, float ambient, float diffuse, float specular, float shininess)
    : m_color(color), m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess),
      m_refractive_index(1.0f), m_opacity(1.0f) {}

const Color& Material::getColor() const {
    return m_color;
}

void Material::setColor(const Color& color) {
    m_color = color;
}

float Material::getAmbient() const {
    return m_ambient;
}

void Material::setAmbient(float ambient) {
    m_ambient = ambient;
}

float Material::getDiffuse() const {
    return m_diffuse;
}

void Material::setDiffuse(float diffuse) {
    m_diffuse = diffuse;
}

float Material::getSpecular() const {
    return m_specular;
}

void Material::setSpecular(float specular) {
    m_specular = specular;
}

float Material::getShininess() const {
    return m_shininess;
}

void Material::setShininess(float shininess) {
    m_shininess = shininess;
}

const Texture& Material::getTexture() const {
    return m_texture;
}

void Material::setTexture(const Texture& texture) {
    m_texture = texture;
}

float Material::getRefractiveIndex() const {
    return m_refractive_index;
}

void Material::setRefractiveIndex(float refractive_index) {
    m_refractive_index = refractive_index;
}

float Material::getOpacity() const {
    return m_opacity;
}

void Material::setOpacity(float opacity) {
    m_opacity = opacity;
}

Color Material::computeDiffuse(const Color& color, const Vector3& normal, const Vector3& light_dir) {
    float dot_product = std::max(normal * light_dir, 0.0f);
    return color * dot_product;
}

Color Material::computeSpecular(const Color& color, const Vector3& normal, const Vector3& light_dir,
    const Vector3& view_dir, float shininess) {
    Vector3 reflected_ray = -light_dir.reflect(normal);
    float specular_factor = std::pow(std::max(view_dir * reflected_ray, 0.0f), shininess);
    return color * specular_factor;
}