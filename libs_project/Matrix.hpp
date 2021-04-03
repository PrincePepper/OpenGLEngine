#include <cmath>
#include <iostream>
#include <cassert>
#include <vector>
#include "Vector.hpp"


/***************************************************************************************
  Matrix2
***************************************************************************************/
template<class T>
class Matrix2 {
public:
    Matrix2() : data2(0) {}

    explicit Matrix2(T number) {
        data2[0] = Vector2<T>(number, 0);
        data2[1] = Vector2<T>(0, number);
    }

    Matrix2(T x, T y, T z, T w) {
        data2.x = Vector2<T>(x, y);
        data2.y = Vector2<T>(z, w);
    }

    Matrix2(const Vector2<T> &first, const Vector2<T> &second) {
        data2[0] = first;
        data2[1] = second;
    }

    Matrix2(const Matrix2 &other) {
        data2 = other.data2;
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

    Vector2<T> operator*(const Vector2<T> &other) const {
        Vector2<T> result;
        result.x = data2[0][0] * other.x + data2[1][0] * other.y;
        result.y = data2[0][1] * other.x + data2[1][1] * other.y;
        return result;
    }

    Matrix2 operator/(float number) const {
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

    Vector2<T> GetColumn(int index) {
        assert(index >= 0 && index < 2);
        return Vector2(data2[index][0], data2[index][1]);
    }

    Vector2<T> GetRow(int index) {
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
        float det = data2[0][0] * data2[1][1] - data2[1][0] * data2[0][1];
        Matrix2 result;
        result.data[0][0] = data2[1][1] * (1 / det);
        result.data[0][1] = -data2[0][1] * (1 / det);
        result.data[1][0] = -data2[1][0] * (1 / det);
        result.data[1][1] = data2[0][0] * (1 / det);
        return result;
    }

    bool operator==(const Matrix2 &other) const {
        return data2.x == other.x && data2.y == other.y;
    }

    bool operator!=(const Matrix2 &other) const {
        return data2.x != other.x || data2.y != other.y;
    }

private:
    Vector2<Vector2<T>> data2;
};


/***************************************************************************************
  Matrix3
***************************************************************************************/
template<class T>
class Matrix3 {
public:
    Matrix3() : data3(0) {}

    explicit Matrix3(T number) {
        data3[0] = Vector3<T>(number, 0, 0);
        data3[1] = Vector3<T>(0, number, 0);
        data3[1] = Vector3<T>(0, 0, number);
    }

    Matrix3(T x, T y, T z,
            T a, T b, T c,
            T d, T e, T g) {
        data3[0] = Vector3<T>(x, y, z);
        data3[1] = Vector3<T>(a, b, c);
        data3[1] = Vector3<T>(d, e, g);
    }

    Matrix3(const Vector3<T> &first, const Vector2<T> &second, const Vector2<T> &third) {
        data3[0] = first;
        data3[1] = second;
        data3[2] = third;
    }

    Matrix3(const Matrix3 &other) {
        data3 = other.data3;
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
        return Matrix3(
                data3[0][0] * other.data3[0][0] + data3[1][0] * other.data3[0][1],
                data3[0][1] * other.data3[0][0] + data3[1][1] * other.data3[0][1],
                data3[0][0] * other.data3[1][0] + data3[1][0] * other.data3[1][1],
                data3[0][1] * other.data3[1][0] + data3[1][1] * other.data3[1][1]);
    }

    Matrix3 operator*(float number) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                result.data3[i][j] = data3[i][j] * number;
        }
        return result;
    }

    Vector2<T> operator*(const Vector2<T> &other) const {
        Vector2<T> result;
        result.x = data3[0][0] * other.x + data3[1][0] * other.y;
        result.y = data3[0][1] * other.x + data3[1][1] * other.y;
        return result;
    }

    Matrix3 operator/(float number) const {
        Matrix3 result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
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
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data3[i][j] *= number;
        }
        return *this;
    }

    Matrix3 &operator/=(float number) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data3[i][j] /= number;
        }
        return *this;
    }

    Matrix3 &operator+=(float number) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data3[i][j] += number;
        }
        return *this;
    }

    Matrix3 &operator-=(float number) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                data3[i][j] -= number;
        }
        return *this;
    }

    /********************************************
        Useful Vector Operations
    ********************************************/

    Matrix3 GetIdentity() {
        return Matrix3(1.0f);
    }

    Vector2<T> GetColumn(int index) {
        assert(index >= 0 && index < 2);
        return Vector2(data3[index][0], data3[index][1]);
    }

    Vector2<T> GetRow(int index) {
        assert(index >= 0 && index < 2);
        std::vector<float> result(2);
        for (int i = 0; i < 2; i++) {
            result[i] = data3[i][index];
        }
        return Vector2(result[0], result[1]);
    }

    Matrix3 GetTransposed() {
        return Matrix3(GetColumn(0), GetColumn(1));
    }

    Matrix3 GetInverse() {
        float det = data3[0][0] * data3[1][1] - data3[1][0] * data3[0][1];
        Matrix3 result;
        result.data[0][0] = data3[1][1] * (1 / det);
        result.data[0][1] = -data3[0][1] * (1 / det);
        result.data[1][0] = -data3[1][0] * (1 / det);
        result.data[1][1] = data3[0][0] * (1 / det);
        return result;
    }

    bool operator==(const Matrix3 &other) const {
        return data3.x == other.x && data3.y == other.y;
    }

    bool operator!=(const Matrix3 &other) const {
        return data3.x != other.x || data3.y != other.y;
    }

private:
    Vector2<Vector2<T>> data3;
};