#include <iostream>
#include "libs_project/Matrix.hpp"
using namespace std;
int main() {
  // Vector2<double> Vec2(1, 1);
  // Vector3<double> a(1, 0, 0), b(0, 2, 0);
  // cout << cross(a, b * 0.5) << endl;
  // Point3D test=new Point3D<float>(3);
  // Point3D test2=new Point3D<float>(3,4,5,6);
  Matrix2<int> c(1, 1, 1, 1);
  Matrix2<int> d(2, 3, 4, 5);
  Matrix2<int> g;
  g = c * d;
  return 0;
}