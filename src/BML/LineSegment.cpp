#include "BML/LineSegment.h"

LineSegment::LineSegment() : m_start(Vector3::ZERO), m_end(Vector3::ZERO) {}

LineSegment::LineSegment(const Vector3& start, const Vector3& end) : m_start(start), m_end(end) {}

void LineSegment::set(const Vector3& start, const Vector3& end) {
    m_start = start;
    m_end = end;
}

Vector3 LineSegment::getStart() const {
    return m_start;
}

Vector3 LineSegment::getEnd() const {
    return m_end;
}

float LineSegment::getLength() const {
    return (m_end - m_start).length();
}

Vector3 LineSegment::getDirection() const {
    return (m_end - m_start).normalize();
}
