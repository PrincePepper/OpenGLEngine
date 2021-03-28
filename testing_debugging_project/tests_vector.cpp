// #include <iostream>
// #define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
// #include "catch.hpp"
// #include <vector>
// using namespace VM;
// using namespace std;

//Vector2<double> Vec2(1, 1);
//  Vector3<double> a(1, 0, 0), b(0, 2, 0);
//  cout << cross(a, b * 0.5) << endl;

// TEST_CASE("LAB") {
//   SECTION("Complex numbers") {
//     SECTION("creating a class and writing and comparing with itself") {
//       Complex<int> a_int(5, 2);
//       Complex<int> b_int(3, -3);
//       Complex<int> c_int(3, 0);
//       Complex<int> d_int(4);
//       Complex<int> e_int = 7;
//       a_int = a_int;
//       b_int = b_int;
//       c_int = c_int;
//
//       REQUIRE(a_int == a_int);
//       REQUIRE(b_int == b_int);
//       REQUIRE(c_int == c_int);
//       REQUIRE(d_int.GetReal() == 4);
//       REQUIRE(d_int.GetImaginary() == 0);
//       REQUIRE(e_int.GetReal() == 7);
//       REQUIRE(e_int.GetImaginary() == 0);
//
//       Complex<int> kopy = Complex<int>(8, 3);
//       Complex<int> dCopy(kopy);
//       dCopy += 5;
//       REQUIRE(dCopy == kopy + 5);
//     }
//   }
// }
#include <iostream>

#include "../libs_project/Vector.hpp"

using std::cout;
using std::endl;

int main() {
  Vector2<double> Vec2(1, 1);
  Vector3<double> a(1, 0, 0), b(0, 2, 0);
  cout << cross(a, b) << endl;
  return 0;
}