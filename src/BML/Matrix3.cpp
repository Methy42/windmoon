#include "BML/Matrix3.h"

// 构造函数
Matrix3::Matrix3() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m_data[i][j] = 0;
        }
    }
}

Matrix3::Matrix3(float m11, float m12, float m13,
                 float m21, float m22, float m23,
                 float m31, float m32, float m33) {
    m_data[0][0] = m11; m_data[0][1] = m12; m_data[0][2] = m13;
    m_data[1][0] = m21; m_data[1][1] = m22; m_data[1][2] = m23;
    m_data[2][0] = m31; m_data[2][1] = m32; m_data[2][2] = m33;
}

// 拷贝构造函数
Matrix3::Matrix3(const Matrix3& m) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m_data[i][j] = m.m_data[i][j];
        }
    }
}

// 矩阵加法
Matrix3 Matrix3::operator+(const Matrix3& m) const {
    Matrix3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.set(i, j, m_data[i][j] + m.get(i, j));
        }
    }
    return result;
}

// 矩阵减法
Matrix3 Matrix3::operator-(const Matrix3& m) const {
    Matrix3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.set(i, j, m_data[i][j] - m.get(i, j));
        }
    }
    return result;
}

// 矩阵乘法
Matrix3 Matrix3::operator*(const Matrix3& m) const {
    Matrix3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            float sum = 0;
            for (int k = 0; k < 3; ++k) {
                sum += m_data[i][k] * m.get(k, j);
            }
            result.set(i, j, sum);
        }
    }
    return result;
}

// 矩阵标量乘法
Matrix3 Matrix3::operator*(float c) const {
    Matrix3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.set(i, j, m_data[i][j] * c);
        }
    }
    return result;
}

// 矩阵标量除法
Matrix3 Matrix3::operator/(float c) const {
    Matrix3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.set(i, j, m_data[i][j] / c);
        }
    }
    return result;
}

// 矩阵转置
Matrix3 Matrix3::transpose() const {
    Matrix3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.set(j, i, m_data[i][j]);
        }
    }
    return result;
}

// 矩阵求逆
Matrix3 Matrix3::inverse() const {
    float det = m_data[0][0] * (m_data[1][1] * m_data[2][2] - m_data[2][1] * m_data[1][2])
        - m_data[0][1] * (m_data[1][0] * m_data[2][2] - m_data[2][0] * m_data[1][2])
        + m_data[0][2] * (m_data[1][0] * m_data[2][1] - m_data[2][0] * m_data[1][1]);
    if (det == 0)
        return Matrix3();
    float inv_det = 1.0f / det;
    Matrix3 result;
    result.set(0, 0, (m_data[1][1] * m_data[2][2] - m_data[2][1] * m_data[1][2]) * inv_det);
    result.set(0, 1, (m_data[0][2] * m_data[2][1] - m_data[0][1] * m_data[2][2]) * inv_det);
    result.set(0, 2, (m_data[0][1] * m_data[1][2] - m_data[0][2] * m_data[1][1]) * inv_det);
    result.set(1, 0, (m_data[1][2] * m_data[2][0] - m_data[1][0] * m_data[2][2]) * inv_det);
    result.set(1, 1, (m_data[0][0] * m_data[2][2] - m_data[0][2] * m_data[2][0]) * inv_det);
    result.set(1, 2, (m_data[1][0] * m_data[0][2] - m_data[0][0] * m_data[1][2]) * inv_det);
    result.set(2, 0, (m_data[1][0] * m_data[2][1] - m_data[2][0] * m_data[1][1]) * inv_det);
    result.set(2, 1, (m_data[2][0] * m_data[0][1] - m_data[0][0] * m_data[2][1]) * inv_det);
    result.set(2, 2, (m_data[0][0] * m_data[1][1] - m_data[1][0] * m_data[0][1]) * inv_det);
    return result;
}

// 获取矩阵元素
float Matrix3::get(int row, int col) const {
    return m_data[row][col];
}

// 设置矩阵元素
void Matrix3::set(int row, int col, float val) {
    m_data[row][col] = val;
}