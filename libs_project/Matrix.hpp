#include <cmath>
#include <iostream>
#include "Vector.hpp"

/***************************************************************************************
  Matrix2
***************************************************************************************/
template<class T>
class Matrix2 {
 public:
  Matrix2() {
  }

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

  // Matrix2 operator*(float number) const {
  //   Matrix2 result;
  //   for (int i = 0; i < 2; i++) {
  //     for (int j = 0; j < 2; j++)
  //       result.data[i][j] = data[i][j] * number;
  //   }
  //   return result;
  // }
  //
  // Vector2 operator*(const Vector2 &other) const {
  //   Vector2 result;
  //   result.x = data[0][0] * other.x + data[1][0] * other.y;
  //   result.y = data[0][1] * other.x + data[1][1] * other.y;
  //   return result;
  // }
  //
  // Matrix2 operator/(float number) const {
  //   Matrix2 result;
  //   for (int i = 0; i < 2; i++) {
  //     for (int j = 0; j < 2; j++)
  //       result.data[i][j] = data[i][j] / number;
  //   }
  //   return result;
  // }
  //
  // /*******************************************
  //     Modifying Math Operators
  // *******************************************/
  //
  // Matrix2 &operator+=(const Matrix2 &other) {
  //   *this = *this + other;
  //   return *this;
  // }
  //
  // Matrix2 &operator-=(const Matrix2 &other) {
  //   *this = *this - other;
  //   return *this;
  // }
  //
  // Matrix2 &operator*=(const Matrix2 &other) {
  //   *this = *this * other;
  //   return *this;
  // }
  //
  // Matrix2 &operator*=(float number) {
  //   for (int i = 0; i < 2; i++) {
  //     for (int j = 0; j < 2; j++)
  //       data[i][j] *= number;
  //   }
  //   return *this;
  // }
  //
  // Matrix2 &operator/=(float number) {
  //   for (int i = 0; i < 2; i++) {
  //     for (int j = 0; j < 2; j++)
  //       data[i][j] /= number;
  //   }
  //   return *this;
  // }
  //
  // Matrix2 &operator+=(float number) {
  //   for (int i = 0; i < 2; i++) {
  //     for (int j = 0; j < 2; j++)
  //       data[i][j] += number;
  //   }
  //   return *this;
  // }
  //
  // Matrix2 &operator-=(float number) {
  //   for (int i = 0; i < 2; i++) {
  //     for (int j = 0; j < 2; j++)
  //       data[i][j] -= number;
  //   }
  //   return *this;
  // }
  //
  // /********************************************
  //     Useful Vector Operations
  // ********************************************/
  //
  // Matrix2 GetIdentity() {
  //   return Matrix2(1.0f);
  // }
  //
  // Matrix2 GetTransposed() {
  //   return Matrix2(GetColumn(0), GetColumn(1));
  // }
  //
  // Matrix2 GetInverse() {
  //   float det = data[0][0] * data[1][1] - data[1][0] * data[0][1];
  //   Matrix2 result;
  //   result.data[0][0] = data[1][1] * (1 / det);
  //   result.data[0][1] = -data[0][1] * (1 / det);
  //   result.data[1][0] = -data[1][0] * (1 / det);
  //   result.data[1][1] = data[0][0] * (1 / det);
  //   return result;
  // }
  //
  // Vector2 GetColumn(int index) {
  //   assert(index >= 0 && index < 2);
  //   return Vector2(data[index][0], data[index][1]);
  // }
  //
  // Vector2 GetRow(int index) {
  //   assert(index >= 0 && index < 2);
  //   std::vector<float> result(2);
  //   for (int i = 0; i < 2; i++) {
  //     result[i] = data[i][index];
  //   }
  //   return Vector2(result[0], result[1]);
  // }
  //
  // const bool operator==(const Matrix2 &our, const Matrix2 &other) {
  //   return our.data == other.data;
  // }
  //
  // const bool operator!=(const Matrix2 &our, const Matrix2 &other) {
  //   return !(our == other);
  // }
 private:
  Vector2<Vector2<T>> data2;
};