#include "SML/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
    : fov(fov), aspect(aspect), near(near), far(far)
{
}

Matrix4 PerspectiveCamera::getProjectionMatrix() const
{
    return Matrix4::perspective(fov, aspect, near, far);
}

std::vector<FrustumPlane> PerspectiveCamera::getFrustumPlanes() const
{
    std::vector<FrustumPlane> planes;

    // 计算相机坐标系下的视锥体顶点位置
    float tan_fov = tan(fov * 0.5f * M_PI / 180.0f);
    float near_height = 2.0f * tan_fov * near;
    float far_height = 2.0f * tan_fov * far;
    float near_width = near_height * aspect;
    float far_width = far_height * aspect;

    Vector3 near_center = m_position + m_direction * near;
    Vector3 far_center = m_position + m_direction * far;
    Vector3 near_top_left = near_center + m_up * (near_height*0.5f) - getRight() * (near_width*0.5f);
    Vector3 near_top_right = near_center + m_up * (near_height*0.5f) + getRight() * (near_width*0.5f);
    Vector3 near_bottom_left = near_center - m_up * (near_height*0.5f) - getRight() * (near_width*0.5f);
    Vector3 near_bottom_right = near_center - m_up * (near_height*0.5f) + getRight() * (near_width*0.5f);
    Vector3 far_top_left = far_center + m_up * (far_height*0.5f) - getRight() * (far_width*0.5f);
    Vector3 far_top_right = far_center + m_up * (far_height*0.5f) + getRight() * (far_width*0.5f);
    Vector3 far_bottom_left = far_center - m_up * (far_height*0.5f) - getRight() * (far_width*0.5f);
    Vector3 far_bottom_right = far_center - m_up * (far_height*0.5f) + getRight() * (far_width*0.5f);

    // 计算视锥体的六个面
    planes.emplace_back(near_top_right, near_top_left, near_bottom_left);  // 近裁剪面
    planes.emplace_back(far_top_left, far_top_right, far_bottom_right);     // 远裁剪面
    planes.emplace_back(near_top_left, far_top_left, far_bottom_left);      // 左裁剪面
    planes.emplace_back(far_top_right, near_top_right, near_bottom_right);  // 右裁剪面
    planes.emplace_back(near_top_left, near_top_right, far_top_right);      // 上裁剪面
    planes.emplace_back(far_bottom_left, far_bottom_right, near_bottom_right);  // 下裁剪面

    return planes;
}

void PerspectiveCamera::calculateFrustumPlanes()
{
    std::vector<FrustumPlane> planes = getFrustumPlanes();
    for (int i = 0; i < 6; i++) {
        frustum_planes[i] = planes[i];
    }
}

bool PerspectiveCamera::isTriangleInFrustum(const Triangle& triangle) const
{
    // 计算三角形所在平面的法向量和距离
    Vector3 normal = (triangle.v2 - triangle.v1) ^ (triangle.v3 - triangle.v1);
    float distance = normal * triangle.v1;

    // 判断三角形是否在所有裁剪面的同侧
    for (int i = 0; i < 6; i++) {
        const FrustumPlane& plane = frustum_planes[i];

        if (plane.getNormal() * normal > 0.0f) {
            // 如果三角形与平面同侧，检查是否有交点在平面内
            bool inside_plane = false;
            for (int j = 0; j < 3; j++) {
                float d = plane.distanceToPoint(triangle.getVertex(j));
                if (d >= 0.0f) {
                    // 若三角形顶点在平面上，则认为三角形在平面内
                    inside_plane = true;
                    break;
                }
            }
            if (!inside_plane) {
                // 如果没有交点在平面内，三角形不在视锥体内
                return false;
            }
        } else {
            // 如果三角形与平面异侧，检查是否有顶点在平面外
            bool outside_plane = true;
            for (int j = 0; j < 3; j++) {
                float d = plane.distanceToPoint(triangle.getVertex(j));
                if (d >= 0.0f) {
                    // 若三角形顶点在平面内，则认为三角形在平面内
                    outside_plane = false;
                    break;
                }
            }
            if (outside_plane) {
                // 如果所有顶点都在平面外，三角形不在视锥体内
                return false;
            }
        }
    }

    return true;
}

// 投影点到平面上
Vector3 PerspectiveCamera::projectOnPlanes(const Vector3& point) const {
    Vector3 projected_point = point;

    for (const auto& plane : frustum_planes) {
        float distance = plane.distanceToPoint(projected_point);
        Vector3 normal = plane.getNormal();
        projected_point -= normal * distance;
    }

    return projected_point;
}

Triangle PerspectiveCamera::getTriangleInFrustum(Triangle* triangle) const
{
    Matrix4 projection_matrix = getProjectionMatrix();

    // 将三角形顶点逐个投影到相机投影平面上
    Vector3 v0 = projectOnPlanes(triangle->v1);
    Vector3 v1 = projectOnPlanes(triangle->v2);
    Vector3 v2 = projectOnPlanes(triangle->v3);

    // 将三角形的投影转换为 NDC 坐标系下的坐标
    v0 = projection_matrix * v0;
    v1 = projection_matrix * v1;
    v2 = projection_matrix * v2;

    return Triangle(v0, v1, v2, triangle->tv1, triangle->tv2, triangle->tv3);
}

// Path: src/SML/OrthographicCamera.cpp