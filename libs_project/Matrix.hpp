#pragma ones

#include <cmath>
#include <iostream>
#include "Vector.hpp"


/***************************************************************************************
  Matrix2
***************************************************************************************/
class Matrix2 {
public:
    [[maybe_unused]] explicit Matrix2(float number) {
        data[0][0] = number;
        data[0][1] = 0;
        data[1][0] = 0;
        data[1][1] = number;
    }

    Matrix2(float x, float y, float z, float w) {
        data[0][0] = x;
        data[0][1] = y;
        data[1][0] = z;
        data[1][1] = w;
    }

    Matrix2(const Vector2<float> &first, const Vector2<float> &second) {
        data[0][0] = first.x;
        data[0][1] = first.y;
        data[1][0] = second.x;
        data[1][1] = second.y;
    }

    Matrix2(const Matrix2 &other) {
        data = other.data;
    }

    /*********************************************
        Non modifying math operators
    *********************************************/

    Matrix2 operator+(const Matrix2 &other) const {
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] + other.data[i][j];
        }
        return result;
    }

    Matrix2 operator+(float number) const {
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] + number;
        }
        return result;
    }

    Matrix2 operator-(const Matrix2 &other) const {
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] - other.data[i][j];
        }
        return result;
    }

    Matrix2 operator-(float number) const {
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] - number;
        }
        return result;
    }

    Matrix2 operator*(const Mat2 &other) const {
        return Matrix2(
                data[0][0] * other.data[0][0] + data[1][0] * other.data[0][1],
                data[0][1] * other.data[0][0] + data[1][1] * other.data[0][1],
                data[0][0] * other.data[1][0] + data[1][0] * other.data[1][1],
                data[0][1] * other.data[1][0] + data[1][1] * other.data[1][1]);
    }

    Matrix2 operator*(float number) const {
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] * number;
        }
        return result;
    }

    Vector2 operator*(const Vector2 &other) const {
        Vector2 result;
        result.x = data[0][0] * other.x + data[1][0] * other.y;
        result.y = data[0][1] * other.x + data[1][1] * other.y;
        return result;
    }

    Matrix2 operator/(float number) const {
        Matrix2 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] / number;
        }
        return result;
    }

    /*******************************************
        Modifying Math Operators
    *******************************************/

    Matrix2 &operator+=(const Mat2 &other) {
        *this = *this + other;
        return *this;
    }

    Matrix2 &operator-=(const Mat2 &other) {
        *this = *this - other;
        return *this;
    }

    Matrix2 &operator*=(const Mat2 &other) {
        *this = *this * other;
        return *this;
    }

    Matrix2 &operator*=(float number) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data[i][j] *= number;
        }
        return *this;
    }

    Matrix2 &operator/=(float number) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data[i][j] /= number;
        }
        return *this;
    }

    Matrix2 &operator+=(float number) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data[i][j] += number;
        }
        return *this;
    }

    Matrix2 &operator-=(float number) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data[i][j] -= number;
        }
        return *this;
    }

    /********************************************
        Useful Vector Operations
    ********************************************/

    Matrix2 GetIdentity() {
        return Matrix2(1.0f);
    }

    Matrix2 GetTransposed() {
        return Matrix2(GetColumn(0), GetColumn(1));
    }

    Matrix2 GetInverse() {
        float det = data[0][0] * data[1][1] - data[1][0] * data[0][1];
        Mat2 result;
        result.data[0][0] = data[1][1] * (1 / det);
        result.data[0][1] = -data[0][1] * (1 / det);
        result.data[1][0] = -data[1][0] * (1 / det);
        result.data[1][1] = data[0][0] * (1 / det);
        return result;
    }

    Vector2 GetColumn(int index) {
        assert(index >= 0 && index < 2);
        return Vector2(data[index][0], data[index][1]);
    }

    Vector2 GetRow(int index) {
        assert(index >= 0 && index < 2);
        std::vector<float> result(2);
        for (int i = 0; i < 2; i++) {
            result[i] = data[i][index];
        }
        return Vector2(result[0], result[1]);
    }

    const bool operator==(const Matrix2 &our, const Matrix2 &other) {
        return our.data == other.data;
    }

    const bool operator!=(const Matrix2 &our, const Matrix2 &other) {
        return !(our == other);
    }

private:
    std::array<std::array<float, 2>, 2> data{0};
};