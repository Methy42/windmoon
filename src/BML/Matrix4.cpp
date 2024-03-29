#include "BML/Matrix4.h"

// 构造函数
Matrix4::Matrix4() {
    for (int i = 0; i < 16; ++i) {
        m_data[i] = 0.0f;
    }
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33) {
    m_data[0] = m00;  m_data[1] = m01;  m_data[2] = m02;  m_data[3] = m03;
    m_data[4] = m10;  m_data[5] = m11;  m_data[6] = m12;  m_data[7] = m13;
    m_data[8] = m20;  m_data[9] = m21;  m_data[10] = m22; m_data[11] = m23;
    m_data[12] = m30; m_data[13] = m31; m_data[14] = m32; m_data[15] = m33;
}

Matrix4::Matrix4(const float* data) {
    for (int i = 0; i < 16; ++i) {
        m_data[i] = data[i];
    }
}

// 拷贝构造函数
Matrix4::Matrix4(const Matrix4& mat) {
    for (int i = 0; i < 16; ++i) {
        m_data[i] = mat.m_data[i];
    }
}

// 获取矩阵元素
float Matrix4::get(int row, int col) const {
    return m_data[row * 4 + col];
}

// 设置矩阵元素
void Matrix4::set(int row, int col, float value) {
    m_data[row * 4 + col] = value;
}

// setColumn 方法是用来设置矩阵的某一列的
void Matrix4::setColumn(int col, const Vector3& v) {
    m_data[col] = v.x;
    m_data[col + 4] = v.y;
    m_data[col + 8] = v.z;
}

void Matrix4::setColumn(int col, const Vector4& v) {
    m_data[col] = v.x;
    m_data[col + 4] = v.y;
    m_data[col + 8] = v.z;
    m_data[col + 12] = v.w;
}

// setRow 方法是用来设置矩阵的某一行的
void Matrix4::setRow(int row, const Vector3& v) {
    m_data[row * 4] = v.x;
    m_data[row * 4 + 1] = v.y;
    m_data[row * 4 + 2] = v.z;
}

void Matrix4::setRow(int row, const Vector4& v) {
    m_data[row * 4] = v.x;
    m_data[row * 4 + 1] = v.y;
    m_data[row * 4 + 2] = v.z;
    m_data[row * 4 + 3] = v.w;
}

// 矩阵加减法
Matrix4 Matrix4::operator+(const Matrix4& mat) const {
    Matrix4 result;
    for (int i = 0; i < 16; ++i) {
        result.m_data[i] = m_data[i] + mat.m_data[i];
    }
    return result;
}

Matrix4 Matrix4::operator-(const Matrix4& mat) const {
    Matrix4 result;
    for (int i = 0; i < 16; ++i) {
        result.m_data[i] = m_data[i] - mat.m_data[i];
    }
    return result;
}

// 矩阵乘法
Matrix4 Matrix4::operator*(const Matrix4& mat) const {
    Matrix4 result;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += get(r, k) * mat.get(k, c);
            }
            result.set(r, c, sum);
        }
    }
    return result;
}

Vector3 Matrix4::operator*(const Vector3& v) const {
    float x = get(0, 0) * v.x + get(0, 1) * v.y + get(0, 2) * v.z + get(0, 3);
    float y = get(1, 0) * v.x + get(1, 1) * v.y + get(1, 2) * v.z + get(1, 3);
    float z = get(2, 0) * v.x + get(2, 1) * v.y + get(2, 2) * v.z + get(2, 3);
    return Vector3(x, y, z);
}

// 矩阵标量乘除法
Matrix4 Matrix4::operator*(float c) const {
    Matrix4 result;
    for (int i = 0; i < 16; ++i) {
        result.m_data[i] = m_data[i] * c;
    }
    return result;
}

Matrix4 Matrix4::operator/(float c) const {
    Matrix4 result;
    for (int i = 0; i < 16; ++i) {
        result.m_data[i] = m_data[i] / c;
    }
    return result;
}

// 矩阵转置
Matrix4 Matrix4::transpose() const {
    Matrix4 result;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            result.set(r, c, get(c, r));
        }
    }
    return result;
}

// 矩阵求逆
Matrix4 Matrix4::inverse() const {
    Matrix4 result;

    float a11 = get(0, 0), a12 = get(0, 1), a13 = get(0, 2), a14 = get(0, 3);
    float a21 = get(1, 0), a22 = get(1, 1), a23 = get(1, 2), a24 = get(1, 3);
    float a31 = get(2, 0), a32 = get(2, 1), a33 = get(2, 2), a34 = get(2, 3);
    float a41 = get(3, 0), a42 = get(3, 1), a43 = get(3, 2), a44 = get(3, 3);

    float det =
        a11 * a22 * a33 * a44 + a11 * a23 * a34 * a42
        + a11 * a24 * a32 * a43 - a11 * a22 * a34 * a43
        - a11 * a23 * a32 * a44 - a11 * a24 * a33 * a42
        - a12 * a21 * a33 * a44 - a12 * a23 * a34 * a41
        - a12 * a24 * a31 * a43 + a12 * a21 * a34 * a43
        + a12 * a23 * a31 * a44 + a12 * a24 * a33 * a41
        + a13 * a21 * a32 * a44 + a13 * a22 * a34 * a41
        + a13 * a24 * a31 * a42 - a13 * a21 * a34 * a42
        - a13 * a22 * a31 * a44 - a13 * a24 * a32 * a41
        - a14 * a21 * a32 * a43 - a14 * a22 * a33 * a41
        - a14 * a23 * a31 * a42 + a14 * a21 * a33 * a42
        + a14 * a22 * a31 * a43 + a14 * a23 * a32 * a41;

    if (std::abs(det) < 1e-6f) {
        // 矩阵不可逆，返回单位矩阵
        result = Matrix4();
    }
    else {
        float invdet = 1.0f / det;
        result.set(0, 0, a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43 - a22 * a34 * a43 - a23 * a32 * a44 - a24 * a33 * a42);
        result.set(0, 1, a12 * a34 * a43 + a13 * a32 * a44 + a14 * a33 * a42 - a12 * a33 * a44 - a13 * a34 * a42 - a14 * a32 * a43);
        result.set(0, 2, a12 * a23 * a44 + a13 * a24 * a42 + a14 * a22 * a43 - a12 * a24 * a43 - a13 * a22 * a44 - a14 * a23 * a42);
        result.set(0, 3, a12 * a24 * a33 + a13 * a22 * a34 + a14 * a23 * a32 - a12 * a23 * a34 - a13 * a24 * a32 - a14 * a22 * a33);

        result.set(1, 0, a21 * a34 * a43 + a23 * a31 * a44 + a24 * a33 * a41 - a21 * a33 * a44 - a23 * a34 * a41 - a24 * a31 * a43);
        result.set(1, 1, a11 * a33 * a44 + a13 * a34 * a41 + a14 * a31 * a43 - a11 * a34 * a43 - a13 * a31 * a44 - a14 * a33 * a41);
        result.set(1, 2, a11 * a24 * a43 + a13 * a21 * a44 + a14 * a23 * a41 - a11 * a23 * a44 - a13 * a24 * a41 - a14 * a21 * a43);
        result.set(1, 3, a11 * a23 * a34 + a13 * a24 * a31 + a14 * a21 * a33 - a11 * a24 * a33 - a13 * a21 * a34 - a14 * a23 * a31);

        result.set(2, 0, a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42 - a21 * a34 * a42 - a22 * a31 * a44 - a24 * a32 * a41);
        result.set(2, 1, a11 * a34 * a42 + a12 * a31 * a44 + a14 * a32 * a41 - a11 * a32 * a44 - a12 * a34 * a41 - a14 * a31 * a42);
        result.set(2, 2, a11 * a22 * a44 + a12 * a24 * a41 + a14 * a21 * a42 - a11 * a24 * a42 - a12 * a21 * a44 - a14 * a22 * a41);
        result.set(2, 3, a11 * a24 * a32 + a12 * a21 * a34 + a14 * a22 * a31 - a11 * a22 * a34 - a12 * a24 * a31 - a14 * a21 * a32);

        result.set(3, 0, a21 * a33 * a42 + a22 * a31 * a43 + a23 * a32 * a41 - a21 * a32 * a43 - a22 * a33 * a41 - a23 * a31 * a42);
        result.set(3, 1, a11 * a32 * a43 + a12 * a33 * a41 + a13 * a31 * a42 - a11 * a33 * a42 - a12 * a31 * a43 - a13 * a32 * a41);
        result.set(3, 2, a11 * a23 * a42 + a12 * a21 * a43 + a13 * a22 * a41 - a11 * a22 * a43 - a12 * a23 * a41 - a13 * a21 * a42);
        result.set(3, 3, a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a11 * a23 * a32 - a12 * a21 * a33 - a13 * a22 * a31);

        result = result / det;
    }

    return result;
}

// 获取平移向量
Vector3 Matrix4::getTranslation() const {
    return Vector3(m_data[12], m_data[13], m_data[14]);
}

// 获取旋转矩阵
Matrix4 Matrix4::getRotationMatrix() const {
    Vector3 xAxis(m_data[0], m_data[1], m_data[2]);
    Vector3 yAxis(m_data[4], m_data[5], m_data[6]);
    Vector3 zAxis(m_data[8], m_data[9], m_data[10]);

    Matrix4 rotation;
    rotation.set(0, 0, xAxis.x);
    rotation.set(0, 1, xAxis.y);
    rotation.set(0, 2, xAxis.z);

    rotation.set(1, 0, yAxis.x);
    rotation.set(1, 1, yAxis.y);
    rotation.set(1, 2, yAxis.z);

    rotation.set(2, 0, zAxis.x);
    rotation.set(2, 1, zAxis.y);
    rotation.set(2, 2, zAxis.z);

    return rotation;
}


// 创建平移矩阵
Matrix4 Matrix4::translate(float x, float y, float z) {
    Matrix4 result;
    result.set(0, 3, x);
    result.set(1, 3, y);
    result.set(2, 3, z);
    return result;
}

Matrix4 Matrix4::translate(const Vector3& v) {
    return Matrix4::translate(v.x, v.y, v.z);
}

Matrix4 Matrix4::translate(const Matrix4& mat, float x, float y, float z) {
    Matrix4 translation = Matrix4::translate(x, y, z);
    return mat * translation;
}

Matrix4 Matrix4::translate(const Matrix4& mat, const Vector3& v) {
    return Matrix4::translate(mat, v.x, v.y, v.z);
}

// 创建缩放矩阵
Matrix4 Matrix4::scale(float x, float y, float z) {
    Matrix4 result;
    result.set(0, 0, x);
    result.set(1, 1, y);
    result.set(2, 2, z);
    return result;
}

Matrix4 Matrix4::scale(const Vector3& v) {
    return Matrix4::scale(v.x, v.y, v.z);
}


// 创建绕 X 轴旋转的变换矩阵
Matrix4 Matrix4::rotateX(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    Matrix4 result;
    result.set(1, 1, c);
    result.set(1, 2, -s);
    result.set(2, 1, s);
    result.set(2, 2, c);
    return result;
}

// 创建绕 Y 轴旋转的变换矩阵
Matrix4 Matrix4::rotateY(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    Matrix4 result;
    result.set(0, 0, c);
    result.set(0, 2, s);
    result.set(2, 0, -s);
    result.set(2, 2, c);
    return result;
}

// 创建绕 Z 轴旋转的变换矩阵
Matrix4 Matrix4::rotateZ(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    Matrix4 result;
    result.set(0, 0, c);
    result.set(0, 1, -s);
    result.set(1, 0, s);
    result.set(1, 1, c);
    return result;
}

// 创建绕任意轴旋转矩阵
Matrix4 Matrix4::rotate(float angle, const Vector3& axis) {
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    float oneMinusCosA = 1.0f - cosA;
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    Matrix4 result;
    result.set(0, 0, cosA + oneMinusCosA * x * x);
    result.set(0, 1, oneMinusCosA * x * y - sinA * z);
    result.set(0, 2, oneMinusCosA * x * z + sinA * y);
    result.set(1, 0, oneMinusCosA * y * x + sinA * z);
    result.set(1, 1, cosA + oneMinusCosA * y * y);
    result.set(1, 2, oneMinusCosA * y * z - sinA * x);
    result.set(2, 0, oneMinusCosA * z * x - sinA * y);
    result.set(2, 1, oneMinusCosA * z * y + sinA * x);
    result.set(2, 2, cosA + oneMinusCosA * z * z);

    return result;
}

// Matrix4 Matrix4::rotate(const Quaternion& q) {
//     Matrix4 result;
//     float xx = q.x * q.x;
//     float xy = q.x * q.y;
//     float xz = q.x * q.z;
//     float xw = q.x * q.getW();
//     float yy = q.y * q.y;
//     float yz = q.y * q.z;
//     float yw = q.y * q.getW();
//     float zz = q.z * q.z;
//     float zw = q.z * q.getW();
//     result.set(0, 0, 1.0f - 2.0f * (yy + zz));
//     result.set(0, 1, 2.0f * (xy - zw));
//     result.set(0, 2, 2.0f * (xz + yw));
//     result.set(1, 0, 2.0f * (xy + zw));
//     result.set(1, 1, 1.0f - 2.0f * (xx + zz));
//     result.set(1, 2, 2.0f * (yz - xw));
//     result.set(2, 0, 2.0f * (xz - yw));
//     result.set(2, 1, 2.0f * (yz + xw));
//     result.set(2, 2, 1.0f - 2.0f * (xx + yy));
//     return result;
// }


// 创建从视图空间到裁剪空间的变换矩阵
Matrix4 Matrix4::perspective(float fov, float aspect, float nearPlane, float farPlane) {
    float f = 1.0f / std::tan(fov * 0.5f);
    float nf = 1.0f / (nearPlane - farPlane);
    Matrix4 result;
    result.set(0, 0, f / aspect);
    result.set(1, 1, f);
    result.set(2, 2, (farPlane + nearPlane) * nf);
    result.set(3, 2, -1.0f);
    result.set(2, 3, 2.0f * farPlane * nearPlane * nf);
    result.set(2, 3, (farPlane - nearPlane) * nf);
    result.set(3, 3, 0.0f);
    return result;
}

// 创建从裁剪空间到视图空间的变换矩阵
Matrix4 Matrix4::orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    float lr = 1.0f / (left - right);
    float bt = 1.0f / (bottom - top);
    float nf = 1.0f / (nearPlane - farPlane);
    Matrix4 result;
    result.set(0, 0, -2.0f * lr);
    result.set(1, 1, -2.0f * bt);
    result.set(2, 2, 2.0f * nf);
    result.set(0, 3, (left + right) * lr);
    result.set(1, 3, (top + bottom) * bt);
    result.set(2, 3, (farPlane + nearPlane) * nf);
    return result;
}

// 创建从视图空间到裁剪空间的变换矩阵
Matrix4 Matrix4::lookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
    Vector3 zaxis = (eye - target).normalize();
    Vector3 xaxis = (up ^ zaxis).normalize();
    Vector3 yaxis = (zaxis ^ xaxis).normalize();
    Matrix4 result;
    result.set(0, 0, xaxis.x);
    result.set(0, 1, yaxis.x);
    result.set(0, 2, zaxis.x);
    result.set(0, 3, 0.0f);
    result.set(1, 0, xaxis.y);
    result.set(1, 1, yaxis.y);
    result.set(1, 2, zaxis.y);
    result.set(1, 3, 0.0f);
    result.set(2, 0, xaxis.z);
    result.set(2, 1, yaxis.z);
    result.set(2, 2, zaxis.z);
    result.set(2, 3, 0.0f);
    result.set(3, 0, -(xaxis * eye));
    result.set(3, 1, -(yaxis * eye));
    result.set(3, 2, -(zaxis * eye));
    result.set(3, 3, 1.0f);
    return result;
}

// identity 函数 用于创建单位矩阵
Matrix4 Matrix4::identity() {
    Matrix4 result;
    result.set(0, 0, 1.0f);
    result.set(1, 1, 1.0f);
    result.set(2, 2, 1.0f);
    result.set(3, 3, 1.0f);
    return result;
}

// toString 函数 用于将矩阵转换为字符串
std::string Matrix4::toString() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "[" << m_data[0] << ", " << m_data[4] << ", " << m_data[8] << ", " << m_data[12] << "]" << std::endl;
    ss << "[" << m_data[1] << ", " << m_data[5] << ", " << m_data[9] << ", " << m_data[13] << "]" << std::endl;
    ss << "[" << m_data[2] << ", " << m_data[6] << ", " << m_data[10] << ", " << m_data[14] << "]" << std::endl;
    ss << "[" << m_data[3] << ", " << m_data[7] << ", " << m_data[11] << ", " << m_data[15] << "]" << std::endl;
    return ss.str();
}
