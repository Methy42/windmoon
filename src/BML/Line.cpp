#include "BML/Line.h"

Line::Line()
    : m_start(Vector3()), m_end(Vector3()) {}

Line::Line(const Vector3& start, const Vector3& end)
    : m_start(start), m_end(end) {}

Vector3 Line::getStart() const {
    return m_start;
}

Vector3 Line::getEnd() const {
    return m_end;
}

void Line::setStart(const Vector3& v) {
    m_start = v;
}

void Line::setEnd(const Vector3& v) {
    m_end = v;
}

float Line::length() const {
    return (m_end - m_start).length();
}

Vector3 Line::direction() const {
    return (m_end - m_start).normalize();
}

Vector3 Line::midpoint() const {
    return (m_start + m_end) * 0.5f;
}

Vector3 Line::pointAt(float t) const {
    return m_start + (m_end - m_start) * t;
}

Vector3 Line::getOrigin() const {
    return m_start;
}
