#include "BML/Color.h"

const Color Color::WHITE(255.0f, 255.0f, 255.0f, 255.0f);

Color::Color()
    : m_r(0.0f), m_g(0.0f), m_b(0.0f), m_a(255.0f) {}

Color::Color(float r, float g, float b, float a)
    : m_r(r), m_g(g), m_b(b), m_a(a) {
    // 计算HSV分量值
    float max_value = std::max(m_r, std::max(m_g, m_b));
    float min_value = std::min(m_r, std::min(m_g, m_b));
    float delta = max_value - min_value;
    if (delta < 1e-6f) {
        m_h = 0.0f;
    } else if (m_r >= max_value) {
        m_h = 60.0f * (m_g - m_b) / delta;
    } else if (m_g >= max_value) {
        m_h = 60.0f * (2.0f + (m_b - m_r) / delta);
    } else {
        m_h = 60.0f * (4.0f + (m_r - m_g) / delta);
    }
    if (m_h < 0.0f) {
        m_h += 360.0f;
    }
    m_s = (max_value > 1e-6f) ? delta / max_value : 0.0f;
    m_v = max_value;
}

float Color::getRed() const {
    return m_r;
}

float Color::getGreen() const {
    return m_g;
}

float Color::getBlue() const {
    return m_b;
}

float Color::getAlpha() const {
    return m_a;
}

float Color::getHue() const {
    return m_h;
}

float Color::getSaturation() const {
    return m_s;
}

float Color::getValue() const {
    return m_v;
}

void Color::setRed(float r) {
    m_r = r;
}

void Color::setGreen(float g) {
    m_g = g;
}

void Color::setBlue(float b) {
    m_b = b;
}

void Color::setAlpha(float a) {
    m_a = a;
}

void Color::setHue(float h) {
    m_h = h;
    while (m_h < 0.0f) {
        m_h += 360.0f;
    }
    while (m_h >= 360.0f) {
        m_h -= 360.0f;
    }
    float c = m_v * m_s;
    float x = c * (1.0f - std::fabs(std::fmod(m_h / 60.0f, 2.0f) - 1.0f));
    float m = m_v - c;
    if (m_h < 60.0f) {
        m_r = c + m;
        m_g = x + m;
        m_b = m;
    } else if (m_h < 120.0f) {
        m_r = x + m;
        m_g = c + m;
        m_b = m;
    } else if (m_h < 180.0f) {
        m_r = m;
        m_g = c + m;
        m_b = x + m;
    } else if (m_h < 240.0f) {
        m_r = m;
        m_g = x + m;
        m_b = c + m;
    } else if (m_h < 300.0f) {
        m_r = x + m;
        m_g = m;
        m_b = c + m;
    } else {
        m_r = c + m;
        m_g = m;
        m_b = x + m;
    }
}

void Color::setSaturation(float s) {
    m_s = s;
    float c = m_v * m_s;
    float x = c * (1.0f - std::fabs(std::fmod(m_h / 60.0f, 2.0f) - 1.0f));
    float m = m_v - c;
    if (m_h < 60.0f) {
        m_r = c + m;
        m_g = x + m;
        m_b = m;
    } else if (m_h < 120.0f) {
        m_r = x + m;
        m_g = c + m;
        m_b = m;
    } else if (m_h < 180.0f) {
        m_r = m;
        m_g = c + m;
        m_b = x + m;
    } else if (m_h < 240.0f) {
        m_r = m;
        m_g = x + m;
        m_b = c + m;
    } else if (m_h < 300.0f) {
        m_r = x + m;
        m_g = m;
        m_b = c + m;
    } else {
        m_r = c + m;
        m_g = m;
        m_b = x + m;
    }
}

void Color::setValue(float v) {
    m_v = v;
    float c = m_v * m_s;
    float x = c * (1.0f - std::fabs(std::fmod(m_h / 60.0f, 2.0f) - 1.0f));
    float m = m_v - c;
    if (m_h < 60.0f) {
        m_r = c + m;
        m_g = x + m;
        m_b = m;
    } else if (m_h < 120.0f) {
        m_r = x + m;
        m_g = c + m;
        m_b = m;
    } else if (m_h < 180.0f) {
        m_r = m;
        m_g = c + m;
        m_b = x + m;
    } else if (m_h < 240.0f) {
        m_r = m;
        m_g = x + m;
        m_b = c + m;
    } else if (m_h < 300.0f) {
        m_r = x + m;
        m_g = m;
        m_b = c + m;
    } else {
        m_r = c + m;
        m_g = m;
        m_b = x + m;
    }
}

float Color::getBrightness() const {
    return 0.299f * m_r + 0.587f * m_g + 0.114f * m_b;
}

Color Color::operator+(const Color& c) const {
    return Color(m_r + c.m_r, m_g + c.m_g, m_b + c.m_b, m_a + c.m_a);
}

Color& Color::operator+=(const Color& other) {
    m_r += other.m_r;
    m_g += other.m_g;
    m_b += other.m_b;
    m_a += other.m_a;
    return *this;
}

Color& Color::operator+=(const Vector3& v) {
    m_r += v.x;
    m_g += v.y;
    m_b += v.z;
    return *this;
}

Color Color::operator-(const Color& other) const {
    return Color(m_r - other.m_r, m_g - other.m_g, m_b - other.m_b, m_a - other.m_a);
}

Color& Color::operator-=(const Color& other) {
    m_r -= other.m_r;
    m_g -= other.m_g;
    m_b -= other.m_b;
    m_a -= other.m_a;
    return *this;
}

Color Color::operator*(float s) const {
    return Color(m_r * s, m_g * s, m_b * s, m_a * s);
}

Color Color::operator*(const Color& c) const {
    return Color(m_r * c.m_r, m_g * c.m_g, m_b * c.m_b, m_a * c.m_a);
}

Color Color::operator/(float scalar) const {
    return Color(m_r / scalar, m_g / scalar, m_b / scalar, m_a / scalar);
}

Color& Color::operator/=(float scalar) {
    m_r /= scalar;
    m_g /= scalar;
    m_b /= scalar;
    m_a /= scalar;
    return *this;
}

bool Color::operator==(const Color& other) const {
    return m_r == other.m_r && m_g == other.m_g && m_b == other.m_b && m_a == other.m_a;
}

bool Color::operator!=(const Color& other) const {
    return !(*this == other);
}

std::string Color::toString() const {
    return "Color(" + std::to_string(m_r) + ", " + std::to_string(m_g) + ", " + std::to_string(m_b) + ", " + std::to_string(m_a) + ")";
}

Color Color::lerp(const Color& c1, const Color& c2, float t) {
    // 线性插值颜色c1和c2，系数为t
    return c1 * (1.0f - t) + c2 * t;
}

Color Color::clamp() const {
    return {m_r < 0.0f ? 0.0f : (m_r > 255.0f ? 255.0f : m_r),
            m_g < 0.0f ? 0.0f : (m_g > 255.0f ? 255.0f : m_g),
            m_b < 0.0f ? 0.0f : (m_b > 255.0f ? 255.0f : m_b),
            m_a < 0.0f ? 0.0f : (m_a > 255.0f ? 255.0f : m_a)};
}

Color Color::blend(const Color& c1, const Color& c2, float t) {
    // 混合颜色c1和c2，系数为t
    Color c = c1 * (1.0f - t) + c2 * t;
    return c;
}