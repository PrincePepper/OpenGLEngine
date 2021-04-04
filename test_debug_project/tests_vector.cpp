#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
#include <vector>
#include "../libs_project/Vector.hpp"
#include "../libs/glm/glm/glm.hpp"
using namespace std;

#define EPS 10e-6

template<typename T, typename H>
void compare_vectors(T glm_vector, const H &my_vec) {
  for (int i = 0; i < my_vec.size(); ++i) {
    REQUIRE(abs(glm_vector[i] - my_vec[i]) < EPS);
  }
}

template<typename T, typename H>
void compare_matrix(T glm_matrix, const H &my_mat) {
  for (int i = 0; i < my_mat.size(); ++i) {
    for (int j = 0; j < my_mat.size(); ++j) {
      REQUIRE(std::abs(glm_matrix[i][j] - my_mat[i][j]) < EPS);
    }
  }
}

TEST_CASE("VECTOR") {
  auto *numbers2 = new float[2];
  numbers2[0] = 34.7;
  numbers2[1] = -57.12;

  auto *numbers3 = new float[3];
  numbers3[0] = 17;
  numbers3[1] = 39.272;
  numbers3[2] = -38;

  auto *numbers4 = new float[4];
  numbers4[0] = 74;
  numbers4[1] = 8.467;
  numbers4[2] = -253;
  numbers4[3] = -83.382;

  std::vector<Vector2<float>> my_vectors2 = {
      Vector2<float>(),
      Vector2<float>(-4.36),
      Vector2<float>(11.3, 4),
      Vector2<float>(Vector2<float>()),
      Vector2<float>(numbers2)
  };

  std::vector<Vector3<float>> my_vectors3 = {
      Vector3<float>(),
      Vector3<float>(7.01),
      Vector3<float>(23.22, -13.09, 9),
      Vector3(Vector3<float>()),
      Vector3<float>(numbers3)
  };

  std::vector<Vector4<float>> my_vectors4 = {
      Vector4<float>(),
      Vector4<float>(19.562),
      Vector4<float>(93.293, 17.1, -133, -82.001),
      Vector4<float>(Vector4<float>()),
      Vector4<float>(numbers4)
  };

  std::vector<glm::vec2> glm_vectors2 = {
      glm::vec2(),
      glm::vec2(-4.36),
      glm::vec2(11.3, 4),
      glm::vec2(glm::vec2())
  };

  std::vector<glm::vec3> glm_vectors3 = {
      glm::vec3(),
      glm::vec3(7.01),
      glm::vec3(23.22, -13.09, 9),
      glm::vec3(glm::vec3())
  };

  std::vector<glm::vec4> glm_vectors4 = {
      glm::vec4(),
      glm::vec4(19.562),
      glm::vec4(93.293, 17.1, -133, -82.001),
      glm::vec4(glm::vec4())
  };

  SECTION("Construction of vectors, getters") {

    for (int i = 0; i < 4; ++i) {
      REQUIRE(2 == my_vectors2[i].size());
      compare_vectors<glm::vec2>(glm_vectors2[i], my_vectors2[i]);
    }

    for (int i = 0; i < 4; ++i) {
      REQUIRE(3 == my_vectors3[i].size());
      compare_vectors<glm::vec3>(glm_vectors3[i], my_vectors3[i]);
    }

    for (int i = 0; i < 4; ++i) {
      REQUIRE(4 == my_vectors4[i].size());
      compare_vectors<glm::vec4>(glm_vectors4[i], my_vectors4[i]);
    }
  }

  SECTION("Copy of vectors with assignment operator") {
    for (auto vec: my_vectors2) {
      Vector2<float> vec_copy;
      vec_copy = vec;
      REQUIRE(vec_copy == vec);

      vec = vec;
      REQUIRE(vec == vec);
    }
    for (auto vec: my_vectors3) {
      Vector3<float> vec_copy;
      vec_copy = vec;
      REQUIRE(vec_copy == vec);

      vec = vec;
      REQUIRE(vec == vec);
    }
    for (auto vec: my_vectors4) {
      Vector4<float> vec_copy;
      vec_copy = vec;
      REQUIRE(vec_copy == vec);

      vec = vec;
      REQUIRE(vec == vec);
    }
  }

  SECTION("Vector addition") {
    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        Vector2 res = my_vectors2[i] + my_vectors2[j];
        glm::vec2 glm_res = glm_vectors2[i] + glm_vectors2[j];
        compare_vectors<glm::vec2>(glm_res, res);
      }
    }

    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        Vector3 res = my_vectors3[i] + my_vectors3[j];
        glm::vec3 glm_res = glm_vectors3[i] + glm_vectors3[j];
        compare_vectors<glm::vec3>(glm_res, res);
      }
    }

    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        Vector4 res = my_vectors4[i] + my_vectors4[j];
        glm::vec4 glm_res = glm_vectors4[i] + glm_vectors4[j];
        compare_vectors<glm::vec4>(glm_res, res);
      }
    }

    for (int i = 0; i < 3; ++i) {
      my_vectors2[i] += my_vectors2[i + 1];
      glm_vectors2[i] += glm_vectors2[i + 1];
      compare_vectors<glm::vec2>(glm_vectors2[i], my_vectors2[i]);
    }

    for (int i = 0; i < 3; ++i) {
      my_vectors3[i] += my_vectors3[i + 1];
      glm_vectors3[i] += glm_vectors3[i + 1];
      compare_vectors<glm::vec3>(glm_vectors3[i], my_vectors3[i]);
    }

    for (int i = 0; i < 3; ++i) {
      my_vectors4[i] += my_vectors4[i + 1];
      glm_vectors4[i] += glm_vectors4[i + 1];
      compare_vectors<glm::vec4>(glm_vectors4[i], my_vectors4[i]);
    }
  }

  SECTION("Vector subtraction") {
    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        Vector2 res = my_vectors2[i] - my_vectors2[j];
        glm::vec2 glm_res = glm_vectors2[i] - glm_vectors2[j];
        compare_vectors<glm::vec2>(glm_res, res);
      }
    }

    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        Vector3 res = my_vectors3[i] - my_vectors3[j];
        glm::vec3 glm_res = glm_vectors3[i] - glm_vectors3[j];
        compare_vectors<glm::vec3>(glm_res, res);
      }
    }

    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        Vector4 res = my_vectors4[i] - my_vectors4[j];
        glm::vec4 glm_res = glm_vectors4[i] - glm_vectors4[j];
        compare_vectors<glm::vec4>(glm_res, res);
      }
    }

    for (int i = 0; i < 3; ++i) {
      my_vectors2[i] -= my_vectors2[i + 1];
      glm_vectors2[i] -= glm_vectors2[i + 1];
      compare_vectors<glm::vec2>(glm_vectors2[i], my_vectors2[i]);
    }

    for (int i = 0; i < 3; ++i) {
      my_vectors3[i] -= my_vectors3[i + 1];
      glm_vectors3[i] -= glm_vectors3[i + 1];
      compare_vectors<glm::vec3>(glm_vectors3[i], my_vectors3[i]);
    }

    for (int i = 0; i < 3; ++i) {
      my_vectors4[i] -= my_vectors4[i + 1];
      glm_vectors4[i] -= glm_vectors4[i + 1];
      compare_vectors<glm::vec4>(glm_vectors4[i], my_vectors4[i]);
    }
  }

  SECTION("Scalar product of vectors") {

    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        float res = my_vectors2[i].dot(my_vectors2[j]);
        float glm_res = glm::dot(glm_vectors2[i], glm_vectors2[j]);
        REQUIRE(std::abs(res - glm_res) < EPS);
      }
    }

    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        float res = my_vectors3[i].dot(my_vectors3[j]);
        float glm_res = glm::dot(glm_vectors3[i], glm_vectors3[j]);
        REQUIRE(std::abs(res - glm_res) < EPS);
      }
    }

    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        float res = my_vectors4[i].dot(my_vectors4[j]);
        float glm_res = glm::dot(glm_vectors4[i], glm_vectors4[j]);
        REQUIRE(std::abs(res - glm_res) < EPS);
      }
    }
  }
  numbers2[0] = 34.7;
  numbers2[1] = -57.12;

  numbers3[0] = 17;
  numbers3[1] = 39.272;
  numbers3[2] = -38;

  numbers4[0] = 74;
  numbers4[1] = 8.467;
  numbers4[2] = -253;
  numbers4[3] = -83.382;

  my_vectors2 = {
      Vector2<float>(),
      Vector2<float>(-4.36),
      Vector2<float>(11.3, 4),
      Vector2<float>(Vector2<float>()),
      Vector2<float>(numbers2)
  };

  my_vectors3 = {
      Vector3<float>(),
      Vector3<float>(7.01),
      Vector3<float>(23.22, -13.09, 9),
      Vector3<float>(Vector3<float>())
  };

  my_vectors4 = {
      Vector4<float>(),
      Vector4<float>(19.562),
      Vector4<float>(93.293, 17.1, -133, -82.001),
      Vector4<float>(Vector4<float>()),
      Vector4<float>(numbers4)
  };

  glm_vectors2 = {
      glm::vec2(),
      glm::vec2(-4.36),
      glm::vec2(11.3, 4),
      glm::vec2(glm::vec2())
  };

  glm_vectors3 = {
      glm::vec3(),
      glm::vec3(7.01),
      glm::vec3(23.22, -13.09, 9),
      glm::vec3(glm::vec3())
  };

  glm_vectors4 = {
      glm::vec4(),
      glm::vec4(19.562),
      glm::vec4(93.293, 17.1, -133, -82.001),
      glm::vec4(glm::vec4())
  };

  SECTION("Cross product of vectors") {

    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        Vector3 res = cross(my_vectors3[i], my_vectors3[j]);
        glm::vec3 glm_res = glm::cross(glm_vectors3[i], glm_vectors3[j]);
        compare_vectors<glm::vec3>(glm_res, res);
      }
    }

    // REQUIRE_THROWS(Vector3::cross_product(my_vectors3[0], Vector(2)));
  }

  SECTION("Multiply vector by float") {
    std::vector<float> numbers{4.2, -4.2, 0.0};

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        Vector2 res = my_vectors2[i] * num;
        glm::vec2 glm_res = glm_vectors2[i] * num;
        compare_vectors<glm::vec2>(glm_res, res);
      }
    }

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        Vector3 res = my_vectors3[i] * num;
        glm::vec3 glm_res = glm_vectors3[i] * num;
        compare_vectors<glm::vec3>(glm_res, res);
      }
    }

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        Vector4 res = my_vectors4[i] * num;
        glm::vec4 glm_res = glm_vectors4[i] * num;
        compare_vectors<glm::vec4>(glm_res, res);
      }
    }

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        my_vectors2[i] *= num;
        glm_vectors2[i] *= num;
        compare_vectors<glm::vec2>(glm_vectors2[i], my_vectors2[i]);
      }
    }

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        my_vectors3[i] *= num;
        glm_vectors3[i] *= num;
        compare_vectors<glm::vec3>(glm_vectors3[i], my_vectors3[i]);
      }
    }

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        my_vectors4[i] *= num;
        glm_vectors4[i] *= num;
        compare_vectors<glm::vec4>(glm_vectors4[i], my_vectors4[i]);
      }
    }
  }

  SECTION("Divide vector by float") {
    std::vector<float> numbers{4.2, -4.2};

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        Vector2 res = my_vectors2[i] / num;
        glm::vec2 glm_res = glm_vectors2[i] / num;
        compare_vectors<glm::vec2>(glm_res, res);
      }
    }

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        Vector3 res = my_vectors3[i] / num;
        glm::vec3 glm_res = glm_vectors3[i] / num;
        compare_vectors<glm::vec3>(glm_res, res);
      }
    }

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        Vector4 res = my_vectors4[i] / num;
        glm::vec4 glm_res = glm_vectors4[i] / num;
        compare_vectors<glm::vec4>(glm_res, res);
      }
    }

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        my_vectors2[i] /= num;
        glm_vectors2[i] /= num;
        compare_vectors<glm::vec2>(glm_vectors2[i], my_vectors2[i]);
      }
    }

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        my_vectors3[i] /= num;
        glm_vectors3[i] /= num;
        compare_vectors<glm::vec3>(glm_vectors3[i], my_vectors3[i]);
      }
    }

    for (int i = 0; i < 4; ++i) {
      for (auto num: numbers) {
        my_vectors4[i] /= num;
        glm_vectors4[i] /= num;
        compare_vectors<glm::vec4>(glm_vectors4[i], my_vectors4[i]);
      }
    }

  }

  SECTION("Equality and inequality of vectors") {
    my_vectors2 = {
        Vector2<float>(),
        Vector2<float>(-4.36),
        Vector2<float>(11.3, 4),
    };

    my_vectors3 = {
        Vector3<float>(),
        Vector3<float>(7.01),
        Vector3<float>(23.22, -13.09, 9)
    };

    my_vectors4 = {
        Vector4<float>(),
        Vector4<float>(19.562),
        Vector4<float>(93.293, 17.1, -133, -82.001)
    };

    for (int i = 0; i < my_vectors2.size(); i++) {
      for (int j = 0; j < my_vectors2.size(); j++) {
        if (i == j) {
          REQUIRE(my_vectors2[i] == my_vectors2[j]);
          continue;
        }

        REQUIRE(my_vectors2[i] != my_vectors2[j]);
      }
    }

    for (int i = 0; i < my_vectors3.size(); i++) {
      for (int j = 0; j < my_vectors3.size(); j++) {
        if (i == j) {
          REQUIRE(my_vectors3[i] == my_vectors3[j]);
          continue;
        }

        REQUIRE(my_vectors3[i] != my_vectors3[j]);
      }
    }

    for (int i = 0; i < my_vectors4.size(); i++) {
      for (int j = 0; j < my_vectors4.size(); j++) {
        if (i == j) {
          REQUIRE(my_vectors4[i] == my_vectors4[j]);
          continue;
        }

        REQUIRE(my_vectors4[i] != my_vectors4[j]);
      }
    }
  }

  SECTION("Length of vectors") {
    for (int i = 0; i < 4; ++i) {
      float res = my_vectors2[i].length();
      float glm_res = glm::length(glm_vectors2[i]);
      REQUIRE(std::abs(res - glm_res) < EPS);
    }

    for (int i = 0; i < 4; ++i) {
      float res = my_vectors3[i].length();
      float glm_res = glm::length(glm_vectors3[i]);
      REQUIRE(std::abs(res - glm_res) < EPS);
    }

    for (int i = 0; i < 4; ++i) {
      float res = my_vectors4[i].length();
      float glm_res = glm::length(glm_vectors4[i]);
      REQUIRE(std::abs(res - glm_res) < EPS);
    }

  }

  SECTION("Vector normalization") {
    for (int i = 1; i < 3; ++i) {
      Vector2 res = my_vectors2[i].normalize();
      glm::vec2 glm_res = glm::normalize(glm_vectors2[i]);
      compare_vectors<glm::vec2>(glm_res, res);
    }

    for (int i = 1; i < 3; ++i) {
      Vector3 res = my_vectors3[i].normalize();
      glm::vec3 glm_res = glm::normalize(glm_vectors3[i]);
      compare_vectors<glm::vec3>(glm_res, res);
    }

    for (int i = 1; i < 3; ++i) {
      Vector4 res = my_vectors4[i].normalize();
      glm::vec4 glm_res = glm::normalize(glm_vectors4[i]);
      compare_vectors<glm::vec4>(glm_res, res);
    }

    REQUIRE_THROWS(my_vectors2[0].normalize());
    REQUIRE_THROWS(my_vectors3[0].normalize());
    REQUIRE_THROWS(my_vectors4[0].normalize());
  }

  SECTION("Output of vectors") {
    Vector2<float> vec2(1, -6.32);
    Vector3<float> vec3(1, -6.32, 2);
    Vector4<float> vec4(-1.123123, 2, 3.002, 4.363);

    std::ostringstream oss1;
    oss1 << vec2;
    REQUIRE(oss1.str() == "<1, -6.32>");

    std::ostringstream oss2;
    oss2 << vec3;
    REQUIRE(oss2.str() == "<1, -6.32, 2>");

    std::ostringstream oss3;
    oss3 << vec4;
    REQUIRE(oss3.str() == "<-1.12312, 2, 3.002, 4.363>");
  }
}

