#pragma ones

#include <cmath>
#include <iostream>
#include <cassert>
#include <vector>
#include <iomanip>
#include "Vector.hpp"

#ifndef OPENGLENGINE_MATRIX_HPP
#define OPENGLENGINE_MATRIX_HPP

/***************************************************************************************
  Matrix2
***************************************************************************************/
class Matrix2 {
public:
    Matrix2() : data2(1) {
        data2[0] = Vector2<float>(1, 0);
        data2[1] = Vector2<float>(0, 1);
    }

    explicit Matrix2(float number) : data2(1) {
        data2[0] = Vector2<float>(number, number);
        data2[1] = Vector2<float>(number, number);
    }

    Matrix2(float x, float y, float z, float w) : data2(1) {
        data2.x = Vector2<float>(x, y);
        data2.y = Vector2<float>(z, w);
    }

    Matrix2(const Vector2<float> &first, const Vector2<float> &second) : data2(1) {
        data2[0] = first;
        data2[1] = second;
    }

    Matrix2(const Matrix2 &other) : data2(1) {
        data2 = other.data2;
    }

    Matrix2(const float *numbers) : data2(1) {
        data2[0] = numbers[0];
        data2[1] = numbers[1];
    }

    Matrix2(float **numbers) : data2(1) {
        data2 = *numbers;
    }

    Vector2<float> &operator[](int idx) {
        return data2[idx];
    }

    Vector2<float> operator[](int idx) const {
        return data2[idx];
    }

    bool operator==(const Matrix2 &other) const {
        return data2.x == other.data2.x && data2.y == other.data2.y;
    }

    bool operator!=(const Matrix2 &other) const {
        return data2.x != other.data2.x || data2.y != other.data2.y;
    }

    /*********************************************
        Non modifying math operators
    *********************************************/

    Matrix2 operator+(const Matrix2 &other) const {
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data2[i][j] = data2[i][j] + other.data2[i][j];
        }
        return result;
    }

    Matrix2 operator+(float number) const {
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data2[i][j] = data2[i][j] + number;
        }
        return result;
    }

    Matrix2 operator-(const Matrix2 &other) const {
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data2[i][j] = data2[i][j] - other.data2[i][j];
        }
        return result;
    }

    Matrix2 operator-(float number) const {
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data2[i][j] = data2[i][j] - number;
        }
        return result;
    }

    Matrix2 operator*(const Matrix2 &other) const {
        return Matrix2(
                data2[0][0] * other.data2[0][0] + data2[1][0] * other.data2[0][1],
                data2[0][1] * other.data2[0][0] + data2[1][1] * other.data2[0][1],
                data2[0][0] * other.data2[1][0] + data2[1][0] * other.data2[1][1],
                data2[0][1] * other.data2[1][0] + data2[1][1] * other.data2[1][1]);
    }

    Matrix2 operator*(float number) const {
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data2[i][j] = data2[i][j] * number;
        }
        return result;
    }

    Vector2<float> operator*(const Vector2<float> &other) const {
        Vector2<float> result;
        result.x = data2[0][0] * other.x + data2[1][0] * other.y;
        result.y = data2[0][1] * other.x + data2[1][1] * other.y;
        return result;
    }

    Matrix2 operator/(float number) const {
        if (number == 0) {
            throw std::runtime_error("Division by zero");
        }
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data2[i][j] = data2[i][j] / number;
        }
        return result;
    }

    /*******************************************
        Modifying Math Operators
    *******************************************/

    Matrix2 &operator+=(const Matrix2 &other) {
        *this = *this + other;
        return *this;
    }

    Matrix2 &operator-=(const Matrix2 &other) {
        *this = *this - other;
        return *this;
    }

    Matrix2 &operator*=(const Matrix2 &other) {
        *this = *this * other;
        return *this;
    }

    Matrix2 &operator*=(float number) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data2[i][j] *= number;
        }
        return *this;
    }

    Matrix2 &operator/=(float number) {
        if (number == 0) {
            throw std::runtime_error("Division by zero");
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data2[i][j] /= number;
        }
        return *this;
    }

    Matrix2 &operator+=(float number) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data2[i][j] += number;
        }
        return *this;
    }

    Matrix2 &operator-=(float number) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data2[i][j] -= number;
        }
        return *this;
    }

    /********************************************
        Useful Vector Operations
    ********************************************/

    Matrix2 GetIdentity() {
        return Matrix2(1.0f);
    }

    Vector2<float> GetColumn(int index) {
        assert(index >= 0 && index < 2);
        return Vector2(data2[index][0], data2[index][1]);
    }

    Vector2<float> GetRow(int index) {
        assert(index >= 0 && index < 2);
        std::vector<float> result(2);
        for (int i = 0; i < 2; i++) {
            result[i] = data2[i][index];
        }
        return Vector2(result[0], result[1]);
    }

    Matrix2 GetTransposed() {
        return Matrix2(GetColumn(0), GetColumn(1));
    }

    Matrix2 GetInverse() {
        float det = find_determinant();
        std::cout << det;
        if (det == 0) {
            throw std::runtime_error(
                    "Can't calculate inverse matrix. Matrix is degenerate");
        }
        Matrix2 result;
        result.data2[0][0] = data2[1][1] * (1 / det);
        result.data2[0][1] = -data2[0][1] * (1 / det);
        result.data2[1][0] = -data2[1][0] * (1 / det);
        result.data2[1][1] = data2[0][0] * (1 / det);
        return result;
    }

    size_t size() const {
        return 2;
    }

    static Matrix2 identity_matrix() {
        Matrix2 mat;
        for (int i = 0; i < mat.size(); ++i) {
            mat[i][i] = 1;
        }

        return mat;
    }

    Matrix2 transposed() {
        float temp;

        for (int i = 0; i < size(); ++i) {
            for (int j = i; j < size(); ++j) {
                temp = data2[i][j];
                data2[i][j] = data2[j][i];
                data2[j][i] = temp;
            }
        }
        return *this;
    }

    float determinant() const {
        return find_determinant();
    }

    Matrix2 adjugate() const {
        Matrix2 adjugate;

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                Matrix2 Mat_ij;

                int idx = 0;
                for (int k = 0; k < size(); ++k) {
                    for (int l = 0; l < size(); ++l) {
                        if (k == i || l == j) {
                            continue;
                        }
                        Mat_ij[idx / (size() - 1)][idx % (size() - 1)] = data2[k][l];
                        idx++;
                    }
                }

                adjugate[i][j] = Mat_ij.determinant() * std::pow(-1, i + j + 2);
            }
        }

        return adjugate;
    }

    Matrix2 inverse() const {
        float det = this->determinant();
        if (det == 0) {
            throw std::runtime_error("Can't calculate inverse matrix. Matrix is degenerate");
        }

        Matrix2 new_matrix = this->adjugate().transposed();

        return new_matrix * (1 / det);
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix2 &matrix) {
        std::cout << std::setprecision(4) << std::fixed;

        os << "Matrix[size=" << matrix.size() << "x" << matrix.size() << "]: [";
        for (int i = 0; i < matrix.size(); ++i) {
            os << "[";
            for (int j = 0; j < matrix.size(); ++j) {
                std::string end = (j == matrix.size() - 1 ? "], " : ", ");
                if (i == matrix.size() - 1 && i == j) {
                    end = "]]";
                }
                os << matrix[i][j] << end;
            }
        }
        return os;
    }

    Vector2<float> get_row(size_t n) const {
        return data2[n];
    }

    Vector2<float> get_col(size_t n) const {
        Vector2<float> vector;

        for (int i = 0; i < size(); ++i) {
            vector[i] = data2[i][n];
        }

        return vector;
    }

private:
    Vector2<Vector2<float>> data2;

    [[nodiscard]] float find_determinant() const {
        return data2[0][0] * data2[1][1] - data2[0][1] * data2[1][0];
    }

};

/***************************************************************************************
  Matrix3
***************************************************************************************/
class Matrix3 {
public:
    Matrix3() : data3(1) {
        data3[0] = Vector3<float>(1, 0, 0);
        data3[1] = Vector3<float>(0, 1, 0);
        data3[2] = Vector3<float>(0, 0, 1);
    }

    explicit Matrix3(float number) : data3(1) {
        data3[0] = Vector3<float>(number, number, number);
        data3[1] = Vector3<float>(number, number, number);
        data3[2] = Vector3<float>(number, number, number);
    }

    Matrix3(float x, float y, float z,
            float a, float b, float c,
            float d, float e, float g) : data3(1) {
        data3[0] = Vector3<float>(x, y, z);
        data3[1] = Vector3<float>(a, b, c);
        data3[2] = Vector3<float>(d, e, g);
    }

    Matrix3(const Vector3<float> &first,
            const Vector3<float> &second,
            const Vector3<float> &third) : data3(1) {
        data3[0] = first;
        data3[1] = second;
        data3[2] = third;
    }

    Matrix3(const Matrix3 &other) : data3(1) {
        data3 = other.data3;
    }

    Matrix3(float *numbers) : data3(1) {
        data3[0] = numbers[0];
        data3[1] = numbers[1];
        data3[2] = numbers[2];
    }

    Matrix3(float **numbers) : data3(1) {
        data3 = *numbers;
    }

    Vector3<float> &operator[](int idx) {
        return data3[idx];
    }

    Vector3<float> operator[](int idx) const {
        return data3[idx];
    }


    bool operator==(const Matrix3 &other) const {
        return data3.x == other.data3.x && data3.y == other.data3.y
                                           && data3.z == other.data3.z;
    }

    bool operator!=(const Matrix3 &other) const {
        return data3.x != other.data3.x || data3.y != other.data3.y
                                           || data3.z != other.data3.z;
    }

    /*********************************************
        Non modifying math operators
    *********************************************/

    Matrix3 operator+(const Matrix3 &other) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                result.data3[i][j] = data3[i][j] + other.data3[i][j];
        }
        return result;
    }

    Matrix3 operator+(float number) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                result.data3[i][j] = data3[i][j] + number;
        }
        return result;
    }

    Matrix3 operator-(const Matrix3 &other) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                result.data3[i][j] = data3[i][j] - other.data3[i][j];
        }
        return result;
    }

    Matrix3 operator-(float number) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                result.data3[i][j] = data3[i][j] - number;
        }
        return result;
    }

    Matrix3 operator*(const Matrix3 &other) const {
        Matrix3 result(0.f);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    result.data3[i][j] += other.data3[i][k] * data3[k][j];
                }
            }
        }
        return result.GetTransposed();
    }

    Matrix3 operator*(float number) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                result.data3[i][j] = data3[i][j] * number;
        }
        return result;
    }

    Vector3<float> operator*(const Vector3<float> &other) const {
        Vector3<float> result;
        result.x =
                data3[0][0] * other.x + data3[1][0] * other.y + data3[2][0] * other.z;
        result.y =
                data3[0][1] * other.x + data3[1][1] * other.y + data3[2][1] * other.z;
        result.z =
                data3[0][2] * other.x + data3[1][2] * other.y + data3[2][2] * other.z;
        return result;
    }

    Matrix3 operator/(float number) const {
        if (number == 0) {
            throw std::runtime_error("Division by zero");
        }
        Matrix3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                result.data3[i][j] = data3[i][j] / number;
        }
        return result;
    }

    /*******************************************
        Modifying Math Operators
    *******************************************/

    Matrix3 &operator+=(const Matrix3 &other) {
        *this = *this + other;
        return *this;
    }

    Matrix3 &operator-=(const Matrix3 &other) {
        *this = *this - other;
        return *this;
    }

    Matrix3 &operator*=(const Matrix3 &other) {
        *this = *this * other;
        return *this;
    }

    Matrix3 &operator*=(float number) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                data3[i][j] *= number;
        }
        return *this;
    }

    Matrix3 &operator/=(float number) {
        if (number == 0) {
            throw std::runtime_error("Division by zero");
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                data3[i][j] /= number;
        }
        return *this;
    }

    Matrix3 &operator+=(float number) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                data3[i][j] += number;
        }
        return *this;
    }

    Matrix3 &operator-=(float number) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                data3[i][j] -= number;
        }
        return *this;
    }

    /********************************************
        Useful Vector Operations
    ********************************************/

    [[maybe_unused]] static Matrix3 GetIdentity() {
        return Matrix3(1.0f);
    }

    Vector3<float> GetColumn(int index) {
        assert(index >= 0 && index < 3);
        return Vector3<float>(data3[index][0], data3[index][1], data3[index][2]);
    }

    Vector3<float> GetRow(int index) {
        assert(index >= 0 && index < 3);
        std::vector<float> result(3);
        for (int i = 0; i < 3; i++) {
            result[i] = data3[i][index];
        }
        return Vector3<float>(result[0], result[1], result[2]);
    }

    Matrix3 GetTransposed() {
        return Matrix3(GetColumn(0), GetColumn(1), GetColumn(2));
    }

    Matrix3 GetInverse() {
        float det = find_determinant();
        std::cout << det;
        if (det == 0) {
            throw std::runtime_error(
                    "Can't calculate inverse matrix. Matrix is degenerate");
        }

        Matrix3 result;
        result.data3[0][0] =
                (data3[1][1] * data3[2][2] - data3[2][1] * data3[1][2]) * (1 / det);
        result.data3[1][0] =
                -(data3[1][0] * data3[2][2] - data3[2][0] * data3[1][2]) * (1 / det);
        result.data3[2][0] =
                (data3[1][0] * data3[2][1] - data3[2][0] * data3[1][1]) * (1 / det);
        result.data3[0][1] =
                -(data3[0][1] * data3[2][2] - data3[2][1] * data3[0][2]) * (1 / det);
        result.data3[1][1] =
                (data3[0][0] * data3[2][2] - data3[2][0] * data3[0][2]) * (1 / det);
        result.data3[2][1] =
                -(data3[0][0] * data3[2][1] - data3[2][0] * data3[0][1]) * (1 / det);
        result.data3[0][2] =
                (data3[0][1] * data3[1][2] - data3[1][1] * data3[0][2]) * (1 / det);
        result.data3[1][2] =
                -(data3[0][0] * data3[1][2] - data3[1][0] * data3[0][2]) * (1 / det);
        result.data3[2][2] =
                (data3[0][0] * data3[1][1] - data3[1][0] * data3[0][1]) * (1 / det);

        return result;
    }

    size_t size() const {
        return 3;
    }

    static Matrix3 identity_matrix() {
        Matrix3 mat;
        for (int i = 0; i < mat.size(); ++i) {
            mat[i][i] = 1;
        }

        return mat;
    }

    Matrix3 transposed() {
        float temp;

        for (int i = 0; i < size(); ++i) {
            for (int j = i; j < size(); ++j) {
                temp = data3[i][j];
                data3[i][j] = data3[j][i];
                data3[j][i] = temp;
            }
        }
        return *this;
    }

    float determinant() const {
        return find_determinant();
    }

    Matrix3 adjugate() const {
        Matrix3 adjugate;

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                Matrix2 Mat_ij;

                int idx = 0;
                for (int k = 0; k < size(); ++k) {
                    for (int l = 0; l < size(); ++l) {
                        if (k == i || l == j) {
                            continue;
                        }
                        Mat_ij[idx / (size() - 1)][idx % (size() - 1)] = data3[k][l];
                        idx++;
                    }
                }

                adjugate[i][j] = Mat_ij.determinant() * std::pow(-1, i + j + 2);
            }
        }

        return adjugate;
    }

    Matrix3 inverse() const {
        float det = this->determinant();
        if (det == 0) {
            throw std::runtime_error("Can't calculate inverse matrix. Matrix is degenerate");
        }

        Matrix3 new_matrix = this->adjugate().transposed();

        return new_matrix * (1 / det);
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix3 &matrix) {
        std::cout << std::setprecision(4) << std::fixed;

        os << "Matrix[size=" << matrix.size() << "x" << matrix.size() << "]: [";
        for (int i = 0; i < matrix.size(); ++i) {
            os << "[";
            for (int j = 0; j < matrix.size(); ++j) {
                std::string end = (j == matrix.size() - 1 ? "], " : ", ");
                if (i == matrix.size() - 1 && i == j) {
                    end = "]]";
                }
                os << matrix[i][j] << end;
            }
        }
        return os;
    }

    Vector3<float> get_row(size_t n) const {
        return data3[n];
    }

    Vector3<float> get_col(size_t n) const {
        Vector3<float> vector;

        for (int i = 0; i < size(); ++i) {
            vector[i] = data3[i][n];
        }

        return vector;
    }

private:
    Vector3<Vector3<float>> data3;

    [[nodiscard]] float find_determinant() const {
        return data3[0][0] * (data3[1][1] * data3[2][2] - data3[2][1] * data3[1][2])
               - data3[1][0] *
                       (data3[0][1] * data3[2][2] - data3[2][1] * data3[0][2])
               + data3[2][0] *
                       (data3[0][1] * data3[1][2] - data3[1][1] * data3[0][2]);
    }
};

/***************************************************************************************
  Matrix4
***************************************************************************************/
class Matrix4 {
public:
    Matrix4() : data4(1) {
        data4[0] = Vector4<float>(1, 0, 0, 0);
        data4[1] = Vector4<float>(0, 1, 0, 0);
        data4[2] = Vector4<float>(0, 0, 1, 0);
        data4[3] = Vector4<float>(0, 0, 0, 1);
    }

    explicit Matrix4(float number) : data4(1) {
        data4[0] = Vector4<float>(number, number, number, number);
        data4[1] = Vector4<float>(number, number, number, number);
        data4[2] = Vector4<float>(number, number, number, number);
        data4[3] = Vector4<float>(number, number, number, number);
    }

    Matrix4(float x, float y, float z, float t,
            float a, float b, float c, float d,
            float e, float f, float g, float h,
            float u, float w, float j, float i) : data4(1) {
        data4[0] = Vector4<float>(x, y, z, t);
        data4[1] = Vector4<float>(a, b, c, d);
        data4[2] = Vector4<float>(e, f, g, h);
        data4[3] = Vector4<float>(u, w, j, i);
    }

    Matrix4(const Vector4<float> &first,
            const Vector4<float> &second,
            const Vector4<float> &third,
            const Vector4<float> &four) : data4(1) {
        data4[0] = first;
        data4[1] = second;
        data4[2] = third;
        data4[3] = four;
    }

    Matrix4(const Matrix4 &other) : data4(1) {
        data4 = other.data4;
    }

    Matrix4(const float *numbers) : data4(1) {
        data4[0] = numbers[0];
        data4[1] = numbers[1];
        data4[2] = numbers[2];
        data4[3] = numbers[3];
    }

    Matrix4(float **numbers) : data4(1) {
        data4 = *numbers;
    }

    Vector4<float> &operator[](int idx) {
        return data4[idx];
    }

    Vector4<float> operator[](int idx) const {
        return data4[idx];
    }

    bool operator==(const Matrix4 &other) const {
        return data4.x == other.data4.x && data4.y == other.data4.y
                                           && data4.z == other.data4.z && data4.w == other.data4.w;
    }

    bool operator!=(const Matrix4 &other) const {
        return data4.x != other.data4.x || data4.y != other.data4.y
                                           || data4.z != other.data4.z || data4.w != other.data4.w;
    }

    /*********************************************
        Non modifying math operators
    *********************************************/

    Matrix4 operator+(const Matrix4 &other) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                result.data4[i][j] = data4[i][j] + other.data4[i][j];
        }
        return result;
    }

    Matrix4 operator+(float number) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                result.data4[i][j] = data4[i][j] + number;
        }
        return result;
    }

    Matrix4 operator-(const Matrix4 &other) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                result.data4[i][j] = data4[i][j] - other.data4[i][j];
        }
        return result;
    }

    Matrix4 operator-(float number) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                result.data4[i][j] = data4[i][j] - number;
        }
        return result;
    }

    Matrix4 operator*(const Matrix4 &other) const {
        Matrix4 result(0.f);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    result.data4[i][j] += other.data4[i][k] * data4[k][j];
                }
            }
        }
        return result.GetTransposed();
    }

    Matrix4 operator*(float number) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                result.data4[i][j] = data4[i][j] * number;
        }
        return result;
    }

    Vector4<float> operator*(const Vector4<float> &other) const {
        Vector4<float> result;
        result.x =
                data4[0][0] * other.x + data4[1][0] * other.y + data4[2][0] * other.z
                + data4[3][0] * other.w;
        result.y =
                data4[0][1] * other.x + data4[1][1] * other.y + data4[2][1] * other.z
                + data4[3][1] * other.w;
        result.z =
                data4[0][2] * other.x + data4[1][2] * other.y + data4[2][2] * other.z
                + data4[3][2] * other.w;
        result.w =
                data4[0][3] * other.x + data4[1][3] * other.y + data4[2][3] * other.z
                + data4[3][3] * other.w;

        return result;
    }

    Matrix4 operator/(float number) const {
        if (number == 0) {
            throw std::runtime_error("Division by zero");
        }
        Matrix4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                result.data4[i][j] = data4[i][j] / number;
        }
        return result;
    }

    /*******************************************
        Modifying Math Operators
    *******************************************/

    Matrix4 &operator+=(const Matrix4 &other) {
        *this = *this + other;
        return *this;
    }

    Matrix4 &operator-=(const Matrix4 &other) {
        *this = *this - other;
        return *this;
    }

    Matrix4 &operator*=(const Matrix4 &other) {
        *this = *this * other;
        return *this;
    }

    Matrix4 &operator*=(float number) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                data4[i][j] *= number;
        }
        return *this;
    }

    Matrix4 &operator/=(float number) {
        if (number == 0) {
            throw std::runtime_error("Division by zero");
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                data4[i][j] /= number;
        }
        return *this;
    }

    Matrix4 &operator+=(float number) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                data4[i][j] += number;
        }
        return *this;
    }

    Matrix4 &operator-=(float number) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                data4[i][j] -= number;
        }
        return *this;
    }

    /********************************************
        Useful Vector Operations
    ********************************************/

    [[maybe_unused]] static Matrix4 GetIdentity() {
        return Matrix4(1.0f);
    }

    Vector4<float> GetColumn(int index) {
        assert(index >= 0 && index < 4);
        return Vector4<float>(data4[index][0],
                              data4[index][1],
                              data4[index][2],
                              data4[index][3]);
    }

    Vector4<float> GetRow(int index) {
        assert(index >= 0 && index < 4);
        std::vector<float> result(4);
        for (int i = 0; i < 4; i++) {
            result[i] = data4[i][index];
        }
        return Vector4<float>(result[0], result[1], result[2], result[3]);
    }

    Matrix4 GetTransposed() {
        return Matrix4(GetColumn(0), GetColumn(1), GetColumn(2), GetColumn(3));
    }

    Matrix4 GetInverse() {
        float det = determinant();
        std::cout << det;
        if (det == 0) {
            throw std::runtime_error(
                    "Can't calculate inverse matrix. Matrix is degenerate");
        }

        Matrix4 result;
        result.data4[0][0] =
                (data4[1][1] * data4[2][2] - data4[2][1] * data4[1][2]) * (1 / det);
        result.data4[1][0] =
                -(data4[1][0] * data4[2][2] - data4[2][0] * data4[1][2]) * (1 / det);
        result.data4[2][0] =
                (data4[1][0] * data4[2][1] - data4[2][0] * data4[1][1]) * (1 / det);
        result.data4[0][1] =
                -(data4[0][1] * data4[2][2] - data4[2][1] * data4[0][2]) * (1 / det);
        result.data4[1][1] =
                (data4[0][0] * data4[2][2] - data4[2][0] * data4[0][2]) * (1 / det);
        result.data4[2][1] =
                -(data4[0][0] * data4[2][1] - data4[2][0] * data4[0][1]) * (1 / det);
        result.data4[0][2] =
                (data4[0][1] * data4[1][2] - data4[1][1] * data4[0][2]) * (1 / det);
        result.data4[1][2] =
                -(data4[0][0] * data4[1][2] - data4[1][0] * data4[0][2]) * (1 / det);
        result.data4[2][2] =
                (data4[0][0] * data4[1][1] - data4[1][0] * data4[0][1]) * (1 / det);

        return result;
    }

    Matrix4 Rotate(float angle, Vector3<float> &vec) {
        float cosAngle = std::cos(angle);
        float sinAngle = std::sin(angle);

        Vector3 axis(vec.normalize());
        Vector3 sup(axis * (1 - cosAngle));

        Matrix4 rotate;
        rotate.data4[0][0] = cosAngle + sup.x * axis.x;
        rotate.data4[0][1] = sup.x * axis.y + sinAngle * axis.z;
        rotate.data4[0][2] = sup.x * axis.z - sinAngle * axis.y;
        rotate.data4[0][3] = 0;

        rotate.data4[1][0] = sup.y * axis.x - sinAngle * axis.z;
        rotate.data4[1][1] = cosAngle + sup.y * axis.y;
        rotate.data4[1][2] = sup.y * axis.z + sinAngle * axis.x;
        rotate.data4[1][3] = 0;

        rotate.data4[2][0] = sup.z * axis.x + sinAngle * axis.y;
        rotate.data4[2][1] = sup.z * axis.y - sinAngle * axis.x;
        rotate.data4[2][2] = cosAngle + sup.z * axis.z;
        rotate.data4[2][3] = 0;

        rotate.data4[3][0] = 0;
        rotate.data4[3][1] = 0;
        rotate.data4[3][2] = 0;
        rotate.data4[3][3] = 1;

        return Matrix4(*this * rotate);
    }

    Matrix4 Translate(const Vector3<float> &vec) {
        Matrix4 result(*this);

        result.data4[3][0] =
                data4[0][0] * vec.x + data4[1][0] * vec.y + data4[2][0] * vec.z
                + data4[3][0];
        result.data4[3][1] =
                data4[0][1] * vec.x + data4[1][1] * vec.y + data4[2][1] * vec.z
                + data4[3][1];
        result.data4[3][2] =
                data4[0][2] * vec.x + data4[1][2] * vec.y + data4[2][2] * vec.z
                + data4[3][2];
        result.data4[3][3] =
                data4[0][3] * vec.x + data4[1][3] * vec.y + data4[2][3] * vec.z
                + data4[3][3];

        return result;
    }

    Matrix4 Scale(const Vector3<float> &vec) {
        Matrix4 result(*this);

        result.data4[0][0] *= vec.x;
        result.data4[0][1] *= vec.x;
        result.data4[0][2] *= vec.x;
        result.data4[0][3] *= vec.x;

        result.data4[1][0] *= vec.y;
        result.data4[1][1] *= vec.y;
        result.data4[1][2] *= vec.y;
        result.data4[1][3] *= vec.y;

        result.data4[2][0] *= vec.z;
        result.data4[2][1] *= vec.z;
        result.data4[2][2] *= vec.z;
        result.data4[2][3] *= vec.z;

        return result;
    }

    [[maybe_unused]]static Matrix4 LookAt(const Vector3<float> &position,
                                          const Vector3<float> &center,
                                          Vector3<float> up) {
        Vector3<float> vecOne(position - center);
        Vector3<float> zaxis(vecOne.normalize());

        Vector3<float> vecUp(up.normalize());
        Vector3<float> vecCross(vecUp.cross(zaxis));
        Vector3<float> xaxis(vecCross.normalize());

        Vector3<float> yaxis(zaxis.cross(xaxis));

        Matrix4 rotation(1.0f);
        rotation.data4[0][0] = xaxis.x;
        rotation.data4[1][0] = xaxis.y;
        rotation.data4[2][0] = xaxis.z;
        rotation.data4[0][1] = yaxis.x;
        rotation.data4[1][1] = yaxis.y;
        rotation.data4[2][1] = yaxis.z;
        rotation.data4[0][2] = zaxis.x;
        rotation.data4[1][2] = zaxis.y;
        rotation.data4[2][2] = zaxis.z;

        Matrix4 translation(1.0f);
        translation.data4[3][0] = -position.x;
        translation.data4[3][1] = -position.y;
        translation.data4[3][2] = -position.z;

        return rotation * translation;
    }

    Matrix4 Perspective(float fovy, float aspect, float nears, float fars) {
        assert(abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);

        float tang = tan(fovy / 2.0f);

        Matrix4 result(0.0f);
        result.data4[0][0] = 1.0f / (aspect * tang);
        result.data4[1][1] = 1.0f / (tang);
        result.data4[2][2] = -(fars + nears) / (fars - nears);
        result.data4[2][3] = -1.0f;
        result.data4[3][2] = -(2.0f * fars * nears) / (fars - nears);
        return result;
    }

    Matrix4 Ortho(float left, float right, float bottom, float top) {
        Matrix4 result(1.0f);
        result.data4[0][0] = 2.0f / (right - left);
        result.data4[1][1] = 2.0f / (top - bottom);
        result.data4[2][2] = -1.0f;
        result.data4[3][0] = -(right + left) / (right - left);
        result.data4[3][1] = -(top + bottom) / (top - bottom);
        return result;
    }

    size_t size() const {
        return 4;
    }

    static Matrix4 identity_matrix() {
        Matrix4 mat;
        for (int i = 0; i < mat.size(); ++i) {
            mat[i][i] = 1;
        }

        return mat;
    }

    Matrix4 transposed() {
        float temp;

        for (int i = 0; i < size(); ++i) {
            for (int j = i; j < size(); ++j) {
                temp = data4[i][j];
                data4[i][j] = data4[j][i];
                data4[j][i] = temp;
            }
        }
        return *this;
    }

    float determinant() const {
        float **newMatrix = new float *[4];
        for (int i = 0; i < 4; i++) {
            newMatrix[i] = new float[4];
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                newMatrix[i][j] = data4[i][j];
            }
        }
        return find_determinant(newMatrix, 4);
    }

    Matrix4 adjugate() const {
        Matrix4 adjugate;

        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                Matrix3 Mat_ij;

                int idx = 0;
                for (int k = 0; k < size(); ++k) {
                    for (int l = 0; l < size(); ++l) {
                        if (k == i || l == j) {
                            continue;
                        }
                        Mat_ij[idx / (size() - 1)][idx % (size() - 1)] = data4[k][l];
                        idx++;
                    }
                }

                adjugate[i][j] = Mat_ij.determinant() * std::pow(-1, i + j + 2);
            }
        }

        return adjugate;
    }

    Matrix4 inverse() const {
        float det = this->determinant();
        if (det == 0) {
            throw std::runtime_error("Can't calculate inverse matrix. Matrix is degenerate");
        }

        Matrix4 new_matrix = this->adjugate().transposed();

        return new_matrix * (1 / det);
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix4 &matrix) {
        std::cout << std::setprecision(4) << std::fixed;

        os << "Matrix[size=" << matrix.size() << "x" << matrix.size() << "]: [";
        for (int i = 0; i < matrix.size(); ++i) {
            os << "[";
            for (int j = 0; j < matrix.size(); ++j) {
                std::string end = (j == matrix.size() - 1 ? "], " : ", ");
                if (i == matrix.size() - 1 && i == j) {
                    end = "]]";
                }
                os << matrix[i][j] << end;
            }
        }
        return os;
    }

    Vector4<float> get_row(size_t n) const {
        return data4[n];
    }

    Vector4<float> get_col(size_t n) const {
        Vector4<float> vector;

        for (int i = 0; i < size(); ++i) {
            vector[i] = data4[i][n];
        }

        return vector;
    }

private:
    Vector4<Vector4<float>> data4;

//    float find_determinant() const {
//        return data4[0][0] * (data4[1][1] * (data4[2][2] * data4[3][3] - data4[2][3] * data4[3][2]) -
//                              data4[2][1] * (data4[1][3] * data4[3][2] - data4[1][2] * data4[3][3]) +
//                              data4[3][1] * (data4[1][2] * data4[2][3] - data4[2][2] * data4[1][3])) -
//               data4[0][1] * (data4[1][0] * (data4[2][2] * data4[3][3] - data4[2][3] * data4[3][2]) -
//                              data4[2][0] * (data4[1][3] * data4[3][2] - data4[1][2] * data4[3][3]) +
//                              data4[3][0] * (data4[1][2] * data4[2][3] - data4[2][2] * data4[1][3])) +
//               data4[0][2] * (data4[1][0] * (data4[2][1] * data4[3][3] - data4[2][3] * data4[3][1]) -
//                              data4[2][0] * (data4[1][3] * data4[3][1] - data4[1][1] * data4[3][3]) +
//                              data4[3][0] * (data4[1][1] * data4[2][3] - data4[2][1] * data4[1][3])) -
//               data4[0][3] * (data4[1][0] * (data4[2][1] * data4[3][2] - data4[2][2] * data4[3][1]) -
//                              data4[2][0] * (data4[1][2] * data4[3][1] - data4[1][1] * data4[3][2]) +
//                              data4[3][0] * (data4[1][1] * data4[2][2] - data4[2][1] * data4[1][2]));
//    }


//Возвращает матрицу matrix без row-ой строки и col-того столбца, результат в newMatrix
    void getMatrixWithoutRowAndCol(float **matrix, int size, int row, int col, float **newMatrix) const {
        int offsetRow = 0; //Смещение индекса строки в матрице
        int offsetCol = 0; //Смещение индекса столбца в матрице
        for (int i = 0; i < size - 1; i++) {
            //Пропустить row-ую строку
            if (i == row) {
                offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
            }

            offsetCol = 0; //Обнулить смещение столбца
            for (int j = 0; j < size - 1; j++) {
                //Пропустить col-ый столбец
                if (j == col) {
                    offsetCol = 1; //Встретили нужный столбец, проускаем его смещением
                }

                newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
            }
        }
    }

//Вычисление определителя матрицы разложение по первой строке
    float find_determinant(float **matrix, int size) const {
        float det = 0;
        float degree = 1; // (-1)^(1+j) из формулы определителя

        //Условие выхода из рекурсии
        if (size == 1) {
            return matrix[0][0];
        }
            //Условие выхода из рекурсии
        else if (size == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        } else {
            //Матрица без строки и столбца
            float **newMatrix = new float *[size - 1];
            for (int i = 0; i < size - 1; i++) {
                newMatrix[i] = new float[size - 1];
            }

            //Раскладываем по 0-ой строке, цикл бежит по столбцам
            for (int j = 0; j < size; j++) {
                //Удалить из матрицы i-ю строку и j-ый столбец
                //Результат в newMatrix

                getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

                //Рекурсивный вызов
                //По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть сумма из формулы)
                //где minor_j - дополнительный минор элемента matrix[0][j]
                // (напомню, что минор это определитель матрицы без 0-ой строки и j-го столбца)
                det = det + (degree * matrix[0][j] * find_determinant(newMatrix, size - 1));
                //"Накручиваем" степень множителя
                degree = -degree;
            }

//            //Чистим память на каждом шаге рекурсии(важно!)
//            for (int i = 0; i < size - 1; i++) {
//                delete[] newMatrix[i];
//            }
//            delete[] newMatrix;
        }

        return det;
    }
};

static Matrix4 scale(const Vector2<float> &other) {
    if (other.size() != 3) {
        throw std::runtime_error("Can't make matrix. Vector dimension is not three");
    }
    Matrix4 matrix;
    return matrix;
}

static Matrix4 scale(const Vector4<float> &other) {
    if (other.size() != 3) {
        throw std::runtime_error("Can't make matrix. Vector dimension is not three");
    }
    Matrix4 matrix;
    return matrix;
}

static Matrix4 scale(const Vector3<float> &other) {
    if (other.size() != 3) {
        throw std::runtime_error("Can't make matrix. Vector dimension is not three");
    }

    Matrix4 matrix;
    for (int i = 0; i < 3; ++i) {
        matrix[i][i] = other[i];
    }
    matrix[3][3] = 1;

    return matrix;
}

static Matrix4 transform(const Vector3<float> &other) {
    if (other.size() != 3) {
        throw std::runtime_error("Can't make matrix. Vector dimension is not three");
    }

    Matrix4 matrix = Matrix4::identity_matrix();
    for (int i = 0; i < 3; ++i) {
        matrix[3][i] = other[i];
    }

    return matrix;
}


static Matrix4 rotate(const float &alpha, const float &beta, const float &gamma) {
    Matrix4 x_matrix = Matrix4::identity_matrix();
    Matrix4 y_matrix = Matrix4::identity_matrix();
    Matrix4 z_matrix = Matrix4::identity_matrix();

    x_matrix[1][1] = std::cos(alpha);
    x_matrix[1][2] = -std::sin(alpha);
    x_matrix[2][1] = std::sin(alpha);
    x_matrix[2][2] = std::cos(alpha);

    y_matrix[0][0] = std::cos(beta);
    y_matrix[0][2] = std::sin(beta);
    y_matrix[2][0] = -std::sin(beta);
    y_matrix[2][2] = std::cos(beta);

    z_matrix[0][0] = std::cos(gamma);
    z_matrix[0][1] = -std::sin(gamma);
    z_matrix[1][0] = std::sin(gamma);
    z_matrix[1][1] = std::cos(gamma);

    return x_matrix * y_matrix * z_matrix;
}

static Matrix4 look_at(const Vector3<float> &from, const Vector3<float> &to, const Vector3<float> &world_up) {
    Matrix4 matrix = Matrix4::identity_matrix();
    Vector3<float> forward((to - from).normalize());
    Vector3<float> right(cross(forward, world_up).normalize());
    Vector3<float> up(cross(right, forward));

    for (int i = 0; i < 3; i++) {
        matrix[i][0] = right[i];
        matrix[i][1] = up[i];
        matrix[i][2] = -forward[i];
    }

    matrix[3][0] = -scalar_product(right, from);
    matrix[3][1] = -scalar_product(up, from);
    matrix[3][2] = scalar_product(forward, from);

    return matrix;
}

static Matrix4 perspective(const float &fov, const float &ratio, const float &nears, const float &fars) {
    Matrix4 matrix;

    matrix[0][0] = 1 / (ratio * std::tan(fov / 2));
    matrix[1][1] = 1 / std::tan(fov / 2);
    matrix[2][2] = (nears + fars) / (nears - fars);
    matrix[2][3] = -1;
    matrix[3][2] = (2 * fars * nears) / (nears - fars);

    return matrix;
}

static Matrix4 ortho(const float &right, const float &left, const float &top, const float &bottom, const float &nears,
                     const float &fars) {
    Matrix4 matrix = Matrix4::identity_matrix();

    matrix[0][0] = -2 / (right - left);
    matrix[0][3] = (right + left) / (right - left);
    matrix[1][1] = -2 / (top - bottom);
    matrix[1][3] = (top + bottom) / (top - bottom);
    matrix[2][2] = -2 / (fars - nears);
    matrix[2][3] = -(fars + nears) / (fars - nears);

    return matrix;
}

#endif //OPENGLENGINE_MATRIX_HPP