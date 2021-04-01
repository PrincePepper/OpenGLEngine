#pragma ones
#include <iostream>
#include <cmath>

/***************************************************************************************
  Vector2  -- 2-D vector class
***************************************************************************************/
template<class T>
class Vector2 {
 public:
  T x, y;

  Vector2(const T &s = T()) : x(s), y(s) {}
  Vector2(const T &x, const T &y) : x(x), y(y) {}
  Vector2(const Vector2<T> &v) : x(v.x), y(v.y) {}

  bool operator==(const Vector2<T> &v) const {
    return x == v.x && y == v.y;
  }
  bool operator!=(const Vector2<T> &v) const {
    return x != v.x || y != v.y;
  }

  // оператор =
  Vector2 &operator=(const Vector2<T> &fresh) = default;

  /**********************************************
    Indexing operator
  **********************************************/
  T &operator[](int i) {
    return *(&x + i);
  }
  const T operator[](int i) const {
    return *(&x + i);
  }

  /*********************************************
    Non modifying math operators
  *********************************************/
  Vector2<T> operator-() const {
    return Vector2<T>(-x, -y);
  }
  Vector2<T> operator+(const Vector2<T> &v) const {
    return Vector2<T>(x + v.x, y + v.y);
  }
  Vector2<T> operator-(const Vector2<T> &v) const {
    return Vector2<T>(x - v.x, y - v.y);
  }
  Vector2<T> operator*(const T &s) const {
    return Vector2<T>(x * s, y * s);
  }
  Vector2<T> operator*(const Vector2<T> &v) const {
    return Vector2<T>(x * v.x, y * v.y);
  }
  Vector2<T> operator/(const T &s) const {
    return Vector2<T>(x / s, y / s);
  }

  // template<class T>
  // Vector2<T> operator*(T s, const Vector2<T> &v) {
  //   return Vector2<T>(s * v.x, s * v.y);
  // }

  /*******************************************
    Modifying Math Operators
  *******************************************/
  Vector2<T> &operator+=(const Vector2<T> &v) {
    x += v.x;
    y += v.y;
    return *this;
  }
  Vector2<T> &operator-=(const Vector2<T> &v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  Vector2<T> &operator*=(const T &s) {
    x *= s;
    y *= s;
    return *this;
  }
  Vector2<T> &operator*=(const Vector2<T> &v) {
    x *= v.x;
    y *= v.y;
    return *this;
  }
  Vector2<T> &operator/=(const T &s) {
    x /= s;
    y /= s;
    return *this;
  }

  /*******************************************
    Cast to T* (lets you use vec2 as T array)
  *******************************************/
  explicit operator const T *() const {
    return static_cast<T *>(&x);
  }
  explicit operator T *() {
    return static_cast<T *>(&x);
  }

  /********************************************
    Useful Vector Operations
  ********************************************/
  T length() const {
    return std::sqrt(x * x + y * y);
  }
  T lengthSq() const {
    return x * x + y * y;
  }
  Vector2<T> &normalize() {
    T length = this->length();
    x /= length;
    y /= length;
    return *this;
  }
  Vector2<T> unit() const {
    T length = length();
    return Vector2<T>(x / length, y / length);
  }
  T dot(const Vector2<T> &v) const {
    return x * v.x + y * v.y;
  }
  T cross(const Vector2<T> &v) const { // 3-D cross product with z assumed 0
    return x * v.y + v.x * y;        // return magnitude of resulting vector
  }
};

/********************************************************
 Basic Trig functions of angle between vectors
********************************************************/
template<class T>
T cos(const Vector2<T> &v1, const Vector2<T> &v2) {
  return dot(v1, v2) / v1.length() / v2.length();
}
template<class T>
T sin(const Vector2<T> &v1, const Vector2<T> &v2) {
  return cross(v1, v2) / v1.length() / v2.length();
}
template<class T>
T tan(const Vector2<T> &v1, const Vector2<T> &v2) {
  return sin(v1, v2) / cos(v1, v2);
}
template<class T>
T angle(const Vector2<T> &v1, const Vector2<T> &v2) {
  return std::acos(cos(v1, v2));
}

template<class T>
T dot(const Vector2<T> &v1, const Vector2<T> &v2) {
  return v1.dot(v2);
}
template<class T>
T cross(const Vector2<T> &v1, const Vector2<T> &v2) {
  return v1.cross(v2);
}

template<class T>
std::ostream &operator<<(std::ostream &outs, const Vector2<T> &v) {
  outs << "<" << v.x << ", " << v.y << ">";
  return outs;
}
template<class T>
std::istream &operator>>(std::istream &ins, Vector2<T> &v) {
  ins >> v.x >> v.y;
  return ins;
}

/*********************************************************************************
 Vector3 -- 3D vector
*********************************************************************************/
template<class T>
class Vector3 {
 public:
  T x, y, z;

  Vector3(const T &s = T()) : x(s), y(s), z(s) {}
  Vector3(const T &x, const T &y, const T &z) : x(x), y(y), z(z) {}
  Vector3(const Vector2<T> &v, const T &s = T()) : x(v.x), y(v.y), z(s) {}
  Vector3(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {}

  bool operator==(const Vector3<T> &v) const {
    return x == v.x && y == v.y && z == v.z;
  }
  bool operator!=(const Vector3<T> &v) const {
    return x != v.x || y != v.y || z != v.z;
  }

  /**********************************************
    Indexing operator
  **********************************************/
  T &operator[](int i) {
    return *(&x + i);
  }
  const T operator[](int i) const {
    return *(&x + i);
  }

  /*********************************************
    Non modifying math operators
  *********************************************/
  Vector3<T> operator-() const {
    return Vector3<T>(-x, -y, -z);
  }
  Vector3<T> operator+(const Vector3<T> &v) const {
    return Vector3<T>(x + v.x, y + v.y, z + v.z);
  }
  Vector3<T> operator-(const Vector3<T> &v) const {
    return Vector3<T>(x - v.x, y - v.y, z - v.z);
  }
  Vector3<T> operator*(const T &s) const {
    return Vector3<T>(x * s, y * s, z * s);
  }
  Vector3<T> operator*(const Vector3<T> &v) const {
    return Vector3<T>(x * v.x, y * v.y, z * v.z);
  }
  Vector3<T> operator/(const T &s) const {
    return Vector3<T>(x / s, y / s, z / s);
  }

  /*******************************************
    Modifying Math Operators
  *******************************************/
  Vector3<T> &operator+=(const Vector3<T> &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Vector3<T> &operator-=(const Vector3<T> &v) {
    x -= v.x;
    y -= v.y;
    y -= v.z;
    return *this;
  }
  Vector3<T> &operator*=(const T &s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }
  Vector3<T> &operator*=(const Vector3<T> &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }
  Vector3<T> &operator/=(const T &s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
  }

  /*******************************************
    Cast to T* (lets you use vec2 as T array)
  *******************************************/
  explicit operator const T *() const {
    return static_cast<T *>(&x);
  }
  explicit operator T *() {
    return static_cast<T *>(&x);
  }

  /********************************************
    Useful Vector Operations
  ********************************************/
  T length() const {
    return std::sqrt(x * x + y * y + z * z);
  }
  T lengthSq() const {
    return x * x + y * y + z * z;
  }
  Vector3<T> &normalize() {
    T length = this->length();
    x /= length;
    y /= length;
    z /= length;
    return *this;
  }
  Vector3<T> unit() const {
    T length = length();
    return Vector3<T>(x / length, y / length, z / length);
  }
  T dot(const Vector3<T> &v) const {
    return x * v.x + y * v.y + z * v.z;
  }
  Vector3<T> cross(const Vector3<T> &v) { /* NOTE this function modifies the vector unlike 2D and non-member versions */
    T x_(x), y_(y), z_(z);
    x = y_ * v.z - z_ * v.y;
    y = z_ * v.x - x_ * v.z;
    z = x_ * v.y - y_ * v.x;
    return *this;
  }
};

template<class T>
Vector3<T> operator*(T s, const Vector3<T> &v) {
  return Vector3<T>(s * v.x, s * v.y, s * v.z);
}

/********************************************************
 Basic Trig functions of angle between vectors
********************************************************/
template<class T>
T cos(const Vector3<T> &v1, const Vector3<T> &v2) {
  return dot(v1, v2) / v1.length() / v2.length();
}
template<class T>
T sin(const Vector3<T> &v1, const Vector3<T> &v2) {
  return cross(v1, v2).length() / v1.length() / v2.length();
}
template<class T>
T tan(const Vector3<T> &v1, const Vector3<T> &v2) {
  return sin(v1, v2) / cos(v1, v2);
}
template<class T>
T angle(const Vector3<T> &v1, const Vector3<T> &v2) {
  return std::acos(cos(v1, v2));
}

template<class T>
T dot(const Vector3<T> &v1, const Vector3<T> &v2) {
  return v1.dot(v2);
}
template<class T>
Vector3<T> cross(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector3<T>(v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x);
}

template<class T>
std::ostream &operator<<(std::ostream &outs, const Vector3<T> &v) {
  outs << "<" << v.x << ", " << v.y << ", " << v.z << ">";
  return outs;
}
template<class T>
std::istream &operator>>(std::istream &ins, Vector3<T> &v) {
  ins >> v.x >> v.y >> v.z;
  return ins;
}

/***************************************************************************************
   Vector4  -- 4D Vector
***************************************************************************************/
template<class T>
class Vector4 {
 public:
  T x, y, z, w;

  Vector4(const T &s = T()) : x(s), y(s), z(s), w(s) {}
  Vector4(const T &x, const T &y, const T &z, const T &w = T()) :
      x(x), y(y), z(z), w(w) {}
  Vector4(const Vector2<T> &v1, const Vector2<T> &v2)
      : x(v1.x), y(v1.y), z(v2.x), w(v2.y) {}
  Vector4(const Vector2<T> &v, const T &z = T(), const T &w = T()) :
      x(v.x), y(v.y), z(z), w(w) {}
  Vector4(const Vector3<T> &v, const T &w = T()) :
      x(v.x), y(v.y), z(v.z), w(w) {}
  Vector4(const Vector4<T> &v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

  bool operator==(const Vector4<T> &v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
  }
  bool operator!=(const Vector4<T> &v) const {
    return x != v.x || y != v.y || z != v.z || w != v.w;
  }

  /**********************************************
    Indexing operator
  **********************************************/
  T &operator[](int i) {
    return *(&x + i);
  }
  T operator[](int i) const {
    return *(&x + i);
  }

  /*********************************************
    Non modifying math operators
  *********************************************/
  Vector4<T> operator-() const {
    return Vector4<T>(-x, -y, -z, -w);
  }
  Vector4<T> operator+(const Vector4<T> &v) const {
    return Vector4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
  }
  Vector4<T> operator-(const Vector4<T> &v) const {
    return Vector4<T>(x - v.x, y - v.y, z - v.z, w + v.w);
  }
  Vector4<T> operator*(const T &s) const {
    return Vector4<T>(x * s, y * s, z * s, w * s);
  }
  Vector4<T> operator*(const Vector4<T> &v) const {
    return Vector4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
  }
  Vector4<T> operator/(const T &s) const {
    return Vector4<T>(x / s, y / s, z / s, w / s);
  }

/*******************************************
  Modifying Math Operators
*******************************************/
  Vector4<T> &operator+=(const Vector4<T> &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }
  Vector4<T> &operator-=(const Vector4<T> &v) {
    x -= v.x;
    y -= v.y;
    y -= v.z;
    w -= v.w;
    return *this;
  }
  Vector4<T> &operator*=(const T &s) {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }
  Vector4<T> &operator*=(const Vector4<T> &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }
  Vector4<T> &operator/=(const T &s) {
    x /= s;
    y /= s;
    z /= s;
    w /= s;
    return *this;
  }

  /*******************************************
    Cast to T* (lets you use vec2 as T array)
  *******************************************/
  explicit operator const T *() const {
    return static_cast<T *>(&x);
  }
  explicit operator T *() {
    return static_cast<T *>(&x);
  }

  /********************************************
    Useful Vector Operations
  ********************************************/
  T length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
  }
  T lengthSq() const {
    return x * x + y * y + z * z + w * w;
  }
  Vector4<T> &normalize() {
    T length = this->length();
    x /= length;
    y /= length;
    z /= length;
    w /= length;
    return *this;
  }
  Vector4<T> unit() const {
    T length = length();
    return Vector3<T>(x / length, y / length, z / length, w / length);
  }
  T dot(const Vector4<T> &v) const {
    return x * v.x + y * v.y + z * v.z + w * v.w;
  }
  Vector4<T> cross(const Vector4<T> &v) {
    T x_(x), y_(y), z_(z), w_(w);
    x = y_ * v.z - z_ * v.y;
    y = z_ * v.x - x_ * v.z;
    z = x_ * v.y - y_ * v.x;
    w = x_ * v.y - y_ * v.x;
    return *this;
  }
};

/********************************************************
 Basic Trig functions of angle between vectors
********************************************************/

template<class T>
T cos(const Vector4<T> &v1, const Vector4<T> &v4) {
  return dot(v1, v4) / v1.length() / v4.length();
}
template<class T>
T sin(const Vector4<T> &v1, const Vector4<T> &v2) {
  return cross(v1, v2).length() / v1.length() / v2.length();
}
template<class T>
T tan(const Vector4<T> &v1, const Vector4<T> &v2) {
  return sin(v1, v2) / cos(v1, v2);
}
template<class T>
T angle(const Vector4<T> &v1, const Vector4<T> &v2) {
  return std::acos(cos(v1, v2));
}
template<class T>
T dot(const Vector4<T> &v1, const Vector4<T> &v2) {
  return v1.dot(v2);
}
template<class T>
Vector4<T> cross(const Vector4<T> &v1, const Vector4<T> &v2) {
  return Vector4<T>(v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x);
}

template<class T>
std::ostream &operator<<(std::ostream &outs, const Vector4<T> &v) {
  outs << "<" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ">";
  return outs;
}
template<class T>
std::istream &operator>>(std::istream &ins, Vector4<T> &v) {
  ins >> v.x >> v.y >> v.z >> v.w;
  return ins;
}

template<class T>
class Point3D {
 public:
  T x, y, z, w;

  Point3D(const T &s = T()) : x(s), y(s), z(s), w(s) {}
  Point3D(const T &x, const T &y, const T &z, const T &w)
      : x(x), y(y), z(z), w(w) {}
  Point3D(const Point3D<T> &p) : x(p.x), y(p.y), z(p.z), w(p.w) {}
  Point3D(const Point3D<T> &p, const Vector3<T> &v) : x(p.x + v.x),
                                                      y(p.y + v.y),
                                                      z(p.z + v.z),
                                                      w(p.w) {}
};