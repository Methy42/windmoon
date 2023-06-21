#ifndef BML_MATRIX4_H
#define BML_MATRIX4_H

#include <cmath>
#include "BML/Vector3.h"
#include "BML/Vector4.h"

class Matrix4 {
public:
    // 构造函数
    Matrix4();
    Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);
    Matrix4(const float* data);

    // 拷贝构造函数
    Matrix4(const Matrix4& mat);

    // 获取矩阵元素
    float get(int row, int col) const;
    // 设置矩阵元素
    void set(int row, int col, float value);

    // setColumn 方法是用来设置矩阵的某一列的
    void setColumn(int col, const Vector3& v);
    void setColumn(int col, const Vector4& v);
    // setRow 方法是用来设置矩阵的某一行的
    void setRow(int row, const Vector3& v);
    void setRow(int row, const Vector4& v);

    // 矩阵加减法
    Matrix4 operator+(const Matrix4& mat) const;
    Matrix4 operator-(const Matrix4& mat) const;

    // 矩阵乘法
    Matrix4 operator*(const Matrix4& mat) const;
    Vector3 operator*(const Vector3& v) const;

    // 矩阵标量乘除法
    Matrix4 operator*(float c) const;
    Matrix4 operator/(float c) const;

    // 矩阵转置
    Matrix4 transpose() const;

    // 矩阵求逆
    Matrix4 inverse() const;

    // 获取平移向量
    Vector3 getTranslation() const;
    // 获取旋转矩阵
    Matrix4 getRotationMatrix() const;

    // 创建平移矩阵
    static Matrix4 translate(float x, float y, float z);
    static Matrix4 translate(const Vector3& v);
    static Matrix4 translate(const Matrix4& mat, float x, float y, float z);
    static Matrix4 translate(const Matrix4& mat, const Vector3& v);
    // 创建缩放矩阵
    static Matrix4 scale(float x, float y, float z);
    static Matrix4 scale(const Vector3& v);
    // 创建绕x轴旋转矩阵
    static Matrix4 rotateX(float angle);
    // 创建绕y轴旋转矩阵
    static Matrix4 rotateY(float angle);
    // 创建绕z轴旋转矩阵
    static Matrix4 rotateZ(float angle);
    // 创建绕任意轴旋转矩阵
    static Matrix4 rotate(float angle, const Vector3& axis);
    // 创建从视图空间到裁剪空间的变换矩阵
    static Matrix4 perspective(float fov, float aspect, float near, float far);
    // 创建从裁剪空间到视图空间的变换矩阵
    static Matrix4 orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    // lookAt函数 用于创建从世界空间到视图空间的变换矩阵
    static Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up);
    // identity 函数 用于创建单位矩阵
    static Matrix4 identity();

private:
    float m_data[16];
};

#endif // BML_MATRIX4_H
