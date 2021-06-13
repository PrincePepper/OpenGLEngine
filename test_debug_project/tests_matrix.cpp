#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include <iostream>
#include <vector>
#include "../libs_project/Matrix.hpp"
#include "../libs/glm/glm/glm.hpp"

using namespace std;

#define EPS 10e-6
#define DET_EPS 10e-3

template<typename T, typename H>
void compare_vectors(T glm_vector, const H &my_vec) {
    for (int i = 0; i < my_vec.size(); ++i) {
        float a = glm_vector[i];
        float b = my_vec[i];
        REQUIRE(std::abs(glm_vector[i] - my_vec[i]) < EPS);
    }
}

template<typename T, typename H>
void compare_matrix(T glm_matrix, const H &my_mat) {
    for (int i = 0; i < my_mat.size(); ++i) {
        for (int j = 0; j < my_mat.size(); ++j) {
            float a = glm_matrix[i][j];
            float b = my_mat[i][j];
            REQUIRE(std::abs(glm_matrix[i][j] - my_mat[i][j]) < EPS);
        }
    }
}

TEST_CASE("Matrix testing") {

    SECTION("Construction of matrix, getters") {
        auto **numbers2 = new float *[2];
        for (int i = 0; i < 2; ++i) {
            numbers2[i] = new float[2];
        }

        numbers2[0][0] = 34.7;
        numbers2[0][1] = -57.12;
        numbers2[1][0] = 39.272;
        numbers2[1][1] = -38;

        auto **numbers3 = new float *[3];
        for (int i = 0; i < 3; ++i) {
            numbers3[i] = new float[3];
        }

        numbers3[0][0] = -17;
        numbers3[0][1] = 39.272;
        numbers3[0][2] = -38.211;
        numbers3[1][0] = 74;
        numbers3[1][1] = 8.467;
        numbers3[1][2] = -2.53;
        numbers3[2][0] = -3.382;
        numbers3[2][1] = 34.72;
        numbers3[2][2] = 57.12;

        auto **numbers4 = new float *[4];
        for (int i = 0; i < 4; ++i) {
            numbers4[i] = new float[4];
        }

        numbers4[0][0] = 74.232;
        numbers4[0][1] = 8.467;
        numbers4[0][2] = -25.3;
        numbers4[0][3] = -83.382;
        numbers4[1][0] = 34.7;
        numbers4[1][1] = -57.12;
        numbers4[1][2] = 39.272;
        numbers4[1][3] = -38.5;
        numbers4[2][0] = -17;
        numbers4[2][1] = 39.272;
        numbers4[2][2] = -38;
        numbers4[2][3] = 74.3;
        numbers4[3][0] = 8.467;
        numbers4[3][1] = -253;
        numbers4[3][2] = -83.382;
        numbers4[3][3] = -34.7;

        std::vector<Matrix2> my_matrix2{
                Matrix2(),
                Matrix2(-4.36),
                Matrix2(11.3, 4, 54, 9),
                Matrix2(Matrix2()),
                Matrix2(numbers2),
        };

        std::vector<Matrix3> my_matrix3{
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3(Matrix3()),
                Matrix3(numbers3)
        };

        std::vector<Matrix4> my_matrix4{
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4(Matrix4()),
                Matrix4(numbers4)
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562),
                glm::mat4(93.293,
                          17.1,
                          -133,
                          -82.001,
                          93,
                          -39.2,
                          -24,
                          -38.34,
                          323,
                          4,
                          8,
                          39.13,
                          48,
                          0.11,
                          23,
                          7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 4; ++i) {
            REQUIRE(2 == my_matrix2[i].size());
            compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
        }

        for (int i = 0; i < 4; ++i) {
            REQUIRE(3 == my_matrix3[i].size());
            compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
        }

        for (int i = 0; i < 4; ++i) {
            REQUIRE(4 == my_matrix4[i].size());
            compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
        }

        for (int i = 0; i < 2; ++i) {
            delete[] numbers2[i];
        }
        delete[] numbers2;

        for (int i = 0; i < 3; ++i) {
            delete[] numbers3[i];
        }
        delete[] numbers3;

        for (int i = 0; i < 4; ++i) {
            delete[] numbers4[i];
        }
        delete[] numbers4;
    }

    SECTION("Copy of matrix with assignment operator") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(),
                Matrix2(-4.36),
                Matrix2{11.3, 4, 54, 9},
        };
        std::vector<Matrix3> my_matrix3 = {
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
        };
        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7}
        };

        for (auto mat: my_matrix2) {
            Matrix2 mat_copy(1);
            mat_copy = mat;
            REQUIRE(mat_copy == mat);

            mat = mat;
            REQUIRE(mat == mat);
        }
        for (auto mat: my_matrix3) {
            Matrix3 mat_copy(1);
            mat_copy = mat;
            REQUIRE(mat_copy == mat);

            mat = mat;
            REQUIRE(mat == mat);
        }
        for (auto mat: my_matrix4) {
            Matrix4 mat_copy(1);
            mat_copy = mat;
            REQUIRE(mat_copy == mat);

            mat = mat;
            REQUIRE(mat == mat);
        }
    }

    SECTION("Matrix addition") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(),
                Matrix2(-4.36),
                Matrix2{11.3, 4, 54, 9},
                Matrix2(Matrix2())
        };

        std::vector<Matrix3> my_matrix3 = {
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3(Matrix3())
        };

        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4(Matrix4())
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562),
                glm::mat4(93.293,
                          17.1,
                          -133,
                          -82.001,
                          93,
                          -39.2,
                          -24,
                          -38.34,
                          323,
                          4,
                          8,
                          39.13,
                          48,
                          0.11,
                          23,
                          7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix2 res = my_matrix2[i] + my_matrix2[j];
                glm::mat2 glm_res = glm_matrix2[i] + glm_matrix2[j];
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix3 res = my_matrix3[i] + my_matrix3[j];
                glm::mat3 glm_res = glm_matrix3[i] + glm_matrix3[j];
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix4 res = my_matrix4[i] + my_matrix4[j];
                glm::mat4 glm_res = glm_matrix4[i] + glm_matrix4[j];
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix2[i] += my_matrix2[i + 1];
            glm_matrix2[i] += glm_matrix2[i + 1];
            compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix3[i] += my_matrix3[i + 1];
            glm_matrix3[i] += glm_matrix3[i + 1];
            compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix4[i] += my_matrix4[i + 1];
            glm_matrix4[i] += glm_matrix4[i + 1];
            compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
        }
    }

    SECTION("Matrix and float addition") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(),
                Matrix2(-4.36),
                Matrix2{11.3, 4, 54, 9},
                Matrix2(Matrix2())
        };

        std::vector<Matrix3> my_matrix3 = {
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3(Matrix3())
        };

        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4(Matrix4())
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562),
                glm::mat4(93.293,
                          17.1,
                          -133,
                          -82.001,
                          93,
                          -39.2,
                          -24,
                          -38.34,
                          323,
                          4,
                          8,
                          39.13,
                          48,
                          0.11,
                          23,
                          7),
                glm::mat4(glm::mat4())
        };

        std::vector<float> numbers{4.2, -4.2, 0.0};

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix2 res = my_matrix2[i] + num;
                glm::mat2 glm_res = glm_matrix2[i] + num;
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix3 res = my_matrix3[i] + num;
                glm::mat3 glm_res = glm_matrix3[i] + num;
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix4 res = my_matrix4[i] + num;
                glm::mat4 glm_res = glm_matrix4[i] + num;
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix2[i] += num;
                glm_matrix2[i] += num;
                compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix3[i] += num;
                glm_matrix3[i] += num;
                compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix4[i] += num;
                glm_matrix4[i] += num;
                compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
            }
        }
    }

    SECTION("Matrix subtraction") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(),
                Matrix2(-4.36),
                Matrix2{11.3, 4, 54, 9},
                Matrix2(Matrix2())
        };

        std::vector<Matrix3> my_matrix3 = {
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3(Matrix3())
        };

        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4(Matrix4())
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562),
                glm::mat4(93.293,
                          17.1,
                          -133,
                          -82.001,
                          93,
                          -39.2,
                          -24,
                          -38.34,
                          323,
                          4,
                          8,
                          39.13,
                          48,
                          0.11,
                          23,
                          7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix2 res = my_matrix2[i] - my_matrix2[j];
                glm::mat2 glm_res = glm_matrix2[i] - glm_matrix2[j];
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix3 res = my_matrix3[i] - my_matrix3[j];
                glm::mat3 glm_res = glm_matrix3[i] - glm_matrix3[j];
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix4 res = my_matrix4[i] - my_matrix4[j];
                glm::mat4 glm_res = glm_matrix4[i] - glm_matrix4[j];
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix2[i] -= my_matrix2[i + 1];
            glm_matrix2[i] -= glm_matrix2[i + 1];
            compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix3[i] -= my_matrix3[i + 1];
            glm_matrix3[i] -= glm_matrix3[i + 1];
            compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix4[i] -= my_matrix4[i + 1];
            glm_matrix4[i] -= glm_matrix4[i + 1];
            compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
        }
    }

    SECTION("Matrix and float subtraction") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(),
                Matrix2(-4.36),
                Matrix2{11.3, 4, 54, 9},
                Matrix2(Matrix2())
        };

        std::vector<Matrix3> my_matrix3 = {
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3(Matrix3())
        };

        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4(Matrix4())
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562),
                glm::mat4(93.293,
                          17.1,
                          -133,
                          -82.001,
                          93,
                          -39.2,
                          -24,
                          -38.34,
                          323,
                          4,
                          8,
                          39.13,
                          48,
                          0.11,
                          23,
                          7),
                glm::mat4(glm::mat4())
        };

        std::vector<float> numbers{4.2, -4.2, 0.0};

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix2 res = my_matrix2[i] - num;
                glm::mat2 glm_res = glm_matrix2[i] - num;
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix3 res = my_matrix3[i] - num;
                glm::mat3 glm_res = glm_matrix3[i] - num;
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix4 res = my_matrix4[i] - num;
                glm::mat4 glm_res = glm_matrix4[i] - num;
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix2[i] -= num;
                glm_matrix2[i] -= num;
                compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix3[i] -= num;
                glm_matrix3[i] -= num;
                compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix4[i] -= num;
                glm_matrix4[i] -= num;
                compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
            }
        }
    }

    SECTION("Multiply matrix by float") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(),
                Matrix2(-4.36),
                Matrix2{11.3, 4, 54, 9},
                Matrix2(Matrix2())
        };

        std::vector<Matrix3> my_matrix3 = {
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3(Matrix3())
        };

        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4(Matrix4())
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562),
                glm::mat4(93.293,
                          17.1,
                          -133,
                          -82.001,
                          93,
                          -39.2,
                          -24,
                          -38.34,
                          323,
                          4,
                          8,
                          39.13,
                          48,
                          0.11,
                          23,
                          7),
                glm::mat4(glm::mat4())
        };

        std::vector<float> numbers{4.2, -4.2, 0.0};

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix2 res = my_matrix2[i] * num;
                glm::mat2 glm_res = glm_matrix2[i] * num;
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix3 res = my_matrix3[i] * num;
                glm::mat3 glm_res = glm_matrix3[i] * num;
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix4 res = my_matrix4[i] * num;
                glm::mat4 glm_res = glm_matrix4[i] * num;
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix2[i] *= num;
                glm_matrix2[i] *= num;
                compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix3[i] *= num;
                glm_matrix3[i] *= num;
                compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix4[i] *= num;
                glm_matrix4[i] *= num;
                compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
            }
        }
    }

    SECTION("Matrix product") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(),
                Matrix2(-4.36),
                Matrix2{11.3, 4, 54, 9},
                Matrix2(Matrix2())
        };

        std::vector<Matrix3> my_matrix3 = {
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3(Matrix3())
        };

        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4(Matrix4())
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562),
                glm::mat4(93.293,
                          17.1,
                          -133,
                          -82.001,
                          93,
                          -39.2,
                          -24,
                          -38.34,
                          323,
                          4,
                          8,
                          39.13,
                          48,
                          0.11,
                          23,
                          7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix2 res = my_matrix2[i] * my_matrix2[j];
                glm::mat2 glm_res = glm_matrix2[i] * glm_matrix2[j];
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix3 res = my_matrix3[i] * my_matrix3[j];
                glm::mat3 glm_res = glm_matrix3[i] * glm_matrix3[j];
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix4 res = my_matrix4[i] * my_matrix4[j];
                glm::mat4 glm_res = glm_matrix4[i] * glm_matrix4[j];
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix2[i] *= my_matrix2[i + 1];
            glm::mat2 temp = glm_matrix2[i] * glm_matrix2[i + 1];
            glm_matrix2[i] = temp;
            compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix3[i] *= my_matrix3[i + 1];
            glm::mat3 temp = glm_matrix3[i] * glm_matrix3[i + 1];
            glm_matrix3[i] = temp;
            compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix4[i] *= my_matrix4[i + 1];
            glm::mat4 temp = glm_matrix4[i] * glm_matrix4[i + 1];
            glm_matrix4[i] = temp;
            compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
        }
    }

    SECTION("Multiply matrix by vector") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(),
                Matrix2(-4.36),
                Matrix2{11.3, 4, 54, 9},
                Matrix2(Matrix2())
        };

        std::vector<Matrix3> my_matrix3 = {
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3(Matrix3())
        };

        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4(Matrix4())
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562),
                glm::mat4(93.293,
                          17.1,
                          -133,
                          -82.001,
                          93,
                          -39.2,
                          -24,
                          -38.34,
                          323,
                          4,
                          8,
                          39.13,
                          48,
                          0.11,
                          23,
                          7),
                glm::mat4(glm::mat4())
        };

        std::vector<Vector2<float>> my_vectors2 = {
                Vector2<float>(),
                Vector2<float>(-4.36),
                Vector2<float>{11.3, 4}
        };

        std::vector<Vector3<float>> my_vectors3 = {
                Vector3<float>(),
                Vector3<float>(7.01),
                Vector3<float>{23.22, -13.09, 9}
        };

        std::vector<Vector4<float>> my_vectors4 = {
                Vector4<float>(),
                Vector4<float>(19.562),
                Vector4<float>{93.293, 17.1, -133, -82.001}
        };

        std::vector<glm::vec2> glm_vectors2 = {
                glm::vec2(),
                glm::vec2(-4.36),
                glm::vec2(11.3, 4)
        };

        std::vector<glm::vec3> glm_vectors3 = {
                glm::vec3(),
                glm::vec3(7.01),
                glm::vec3(23.22, -13.09, 9)
        };

        std::vector<glm::vec4> glm_vectors4 = {
                glm::vec4(),
                glm::vec4(19.562),
                glm::vec4(93.293, 17.1, -133, -82.001)
        };

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                Vector2<float> res = my_matrix2[i] * my_vectors2[j];
                glm::vec2 glm_res = glm_matrix2[i] * glm_vectors2[j];
                compare_vectors(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                Vector3<float> res = my_matrix3[i] * my_vectors3[j];
                glm::vec3 glm_res = glm_matrix3[i] * glm_vectors3[j];
                compare_vectors(glm_res, res);
            }
        }

        Vector4<float> res = my_matrix4[0] * my_vectors4[0];
        glm::vec4 glm_res = glm_matrix4[0] * glm_vectors4[0];
        compare_vectors(glm_res, res);
//        for (int i = 0; i < 4; ++i) {
//            for (int j = 0; j < 3; ++j) {
//                Vector4<float> res = my_matrix4[i] * my_vectors4[j];
//                glm::vec4 glm_res = glm_matrix4[i] * glm_vectors4[j];
//                compare_vectors(glm_res, res);
//            }
//        }
    }

    SECTION("Divide matrix by float") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(),
                Matrix2(-4.36),
                Matrix2{11.3, 4, 54, 9},
                Matrix2(Matrix2())
        };

        std::vector<Matrix3> my_matrix3 = {
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3(Matrix3())
        };

        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4(Matrix4())
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562),
                glm::mat4(93.293,
                          17.1,
                          -133,
                          -82.001,
                          93,
                          -39.2,
                          -24,
                          -38.34,
                          323,
                          4,
                          8,
                          39.13,
                          48,
                          0.11,
                          23,
                          7),
                glm::mat4(glm::mat4())
        };

        std::vector<float> numbers{4.2, -4.2};

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix2 res = my_matrix2[i] / num;
                glm::mat2 glm_res = glm_matrix2[i] / num;
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix3 res = my_matrix3[i] / num;
                glm::mat3 glm_res = glm_matrix3[i] / num;
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix4 res = my_matrix4[i] / num;
                glm::mat4 glm_res = glm_matrix4[i] / num;
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix2[i] /= num;
                glm_matrix2[i] /= num;
                compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix3[i] /= num;
                glm_matrix3[i] /= num;
                compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix4[i] /= num;
                glm_matrix4[i] /= num;
                compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
            }
        }

        REQUIRE_THROWS(my_matrix2[0] / 0);
        REQUIRE_THROWS(my_matrix3[0] / 0);
        REQUIRE_THROWS(my_matrix4[0] / 0);
        REQUIRE_THROWS(my_matrix2[0] /= 0);
        REQUIRE_THROWS(my_matrix3[0] /= 0);
        REQUIRE_THROWS(my_matrix4[0] /= 0);
    }

    SECTION("Equality and inequality of matrix") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(2),
                Matrix2(2, -4.36),
                Matrix2{11.3, 4, 54, 9},
        };
        std::vector<Matrix3> my_matrix3 = {
                Matrix3(3),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
        };
        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
        };

        for (int i = 0; i < my_matrix2.size(); i++) {
            for (int j = 0; j < my_matrix2.size(); j++) {
                if (i == j) {
                    REQUIRE(my_matrix2[i] == my_matrix2[j]);
                    continue;
                }

                REQUIRE(my_matrix2[i] != my_matrix2[j]);
            }
        }
        for (int i = 0; i < my_matrix3.size(); i++) {
            for (int j = 0; j < my_matrix3.size(); j++) {
                if (i == j) {
                    REQUIRE(my_matrix3[i] == my_matrix3[j]);
                    continue;
                }

                REQUIRE(my_matrix3[i] != my_matrix3[j]);
            }
        }
        for (int i = 0; i < my_matrix4.size(); i++) {
            for (int j = 0; j < my_matrix4.size(); j++) {
                if (i == j) {
                    REQUIRE(my_matrix4[i] == my_matrix4[j]);
                    continue;
                }

                REQUIRE(my_matrix4[i] != my_matrix4[j]);
            }
        }
    }

    SECTION("Generation identity matrix") {
        Matrix2 my_mat2 = Matrix2::identity_matrix();
        Matrix3 my_mat3 = Matrix3::identity_matrix();
        Matrix4 my_mat4 = Matrix4::identity_matrix();

        glm::mat2 glm_mat2 = glm::mat2(1);
        glm::mat3 glm_mat3 = glm::mat3(1);
        glm::mat4 glm_mat4 = glm::mat4(1);

        compare_matrix(glm_mat2, my_mat2);
        compare_matrix(glm_mat3, my_mat3);
        compare_matrix(glm_mat4, my_mat4);
    }

    SECTION("Generation transposed matrix") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(),
                Matrix2(-4.36),
                Matrix2{11.3, 4, 54, 9},
                Matrix2(Matrix2())
        };

        std::vector<Matrix3> my_matrix3 = {
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3(Matrix3())
        };

        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4(Matrix4())
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562),
                glm::mat4(93.293,
                          17.1,
                          -133,
                          -82.001,
                          93,
                          -39.2,
                          -24,
                          -38.34,
                          323,
                          4,
                          8,
                          39.13,
                          48,
                          0.11,
                          23,
                          7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 4; ++i) {
            Matrix2 res = my_matrix2[i].transposed();
            glm::mat2 glm_res = glm::transpose(glm_matrix2[i]);
            compare_matrix<glm::mat2>(glm_res, res);
        }

        for (int i = 0; i < 4; ++i) {
            Matrix3 res = my_matrix3[i].transposed();
            glm::mat3 glm_res = glm::transpose(glm_matrix3[i]);
            compare_matrix<glm::mat3>(glm_res, res);
        }

        for (int i = 0; i < 4; ++i) {
            Matrix4 res = my_matrix4[i].transposed();
            glm::mat4 glm_res = glm::transpose(glm_matrix4[i]);
            compare_matrix<glm::mat4>(glm_res, res);
        }
    }

    SECTION("Calculation matrix determinant") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2(),
                Matrix2(-4.36),
                Matrix2{11.3, 4, 54, 9},
                Matrix2(Matrix2())
        };

        std::vector<Matrix3> my_matrix3 = {
                Matrix3(),
                Matrix3(7.01),
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3(Matrix3())
        };

        std::vector<Matrix4> my_matrix4 = {
                Matrix4(),
                Matrix4(19.562),
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4(Matrix4())
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562,
                          19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 4; ++i) {
            float res = my_matrix2[i].determinant();
            float glm_res = glm::determinant(glm_matrix2[i]);
            REQUIRE((glm_res - res) < EPS);
        }

        for (int i = 0; i < 4; ++i) {
            float res = my_matrix3[i].determinant();
            float glm_res = glm::determinant(glm_matrix3[i]);
            REQUIRE((glm_res - res) < DET_EPS);
        }

        for (int i = 0; i < 4; ++i) {
            float res = my_matrix4[i].determinant();
            float glm_res = glm::determinant(glm_matrix4[i]);
            REQUIRE((glm_res - res) < DET_EPS);
        }
    }
    SECTION("Calculation inverse matrix") {
        std::vector<Matrix2> my_matrix2 = {
                Matrix2{11.3, 4, 54, 9},
                Matrix2{72, 8, -3, -39},
                Matrix2{-82.001, 93, -39.2, -24}
        };

        std::vector<Matrix3> my_matrix3 = {
                Matrix3{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix3{-29.3, -42.3, 84.231, 8, 24, 8.33, 4, 12, -48},
                Matrix3{93, -39.2, -24, -38.34, 323, 0, 0, 82, -9}
        };

        std::vector<Matrix4> my_matrix4 = {
                Matrix4{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8,
                        39.13, 48, 0.11, 23, 7},
                Matrix4{-2, -39.3, 17.117, 3, -5, -8, 84, 23.13, -4.3241, 11.3, 4, 54, 9,
                        0, 72, 1},
                Matrix4{Matrix4::identity_matrix()}
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(72, 8, -3, -39),
                glm::mat2(-82.001, 93, -39.2, -24)
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(-29.3, -42.3, 84.231, 8, 24, 8.33, 4, 12, -48),
                glm::mat3(93, -39.2, -24, -38.34, 323, 0, 0, 82, -9)
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(93.293,
                          17.1,
                          -133,
                          -82.001,
                          93,
                          -39.2,
                          -24,
                          -38.34,
                          323,
                          4,
                          8,
                          39.13,
                          48,
                          0.11,
                          23,
                          7),
                glm::mat4(-2,
                          -39.3,
                          17.117,
                          3,
                          -5,
                          -8,
                          84,
                          23.13,
                          -4.3241,
                          11.3,
                          4,
                          54,
                          9,
                          0,
                          72,
                          1),
                glm::mat4(1)
        };

        for (int i = 0; i < 3; ++i) {
            Matrix2 res = my_matrix2[i].inverse();
            glm::mat2 glm_res = glm::inverse(glm_matrix2[i]);
            compare_matrix(glm_res, res);
        }

        for (int i = 0; i < 3; ++i) {
            Matrix3 res = my_matrix3[i].inverse();
            glm::mat3 glm_res = glm::inverse(glm_matrix3[i]);
            compare_matrix(glm_res, res);
        }

        for (int i = 0; i < 3; ++i) {
            Matrix4 res = my_matrix4[i].inverse();
            glm::mat4 glm_res = glm::inverse(glm_matrix4[i]);
            compare_matrix(glm_res, res);
        }
    }

    SECTION("Generation scale matrix") {
        std::vector<Vector3<float>> my_vectors = {
                Vector3<float>(7.01),
                Vector3<float>(-2),
                Vector3<float>{23.22, -13.09, 9},
                Vector3<float>{3, 36, -425.1},
                Vector3<float>{9.34, 421, -24}
        };

        std::vector<glm::vec3> glm_vectors = {
                glm::vec3(7.01, 7.01, 7.01),
                glm::vec3(-2, -2, -2),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(3, 36, -425.1),
                glm::vec3(9.34, 421, -24)
        };

        for (int i = 0; i < 5; ++i) {
            Matrix4 res = scale(my_vectors[i]);
//            glm::mat4 glm_res = glm::scale(glm::mat4(1), glm_vectors[i]);
//            compare_matrix(glm_res, res);
        }

        REQUIRE_THROWS(scale(Vector2<float>()));
        REQUIRE_THROWS(scale(Vector4<float>()));
    }

    SECTION("Generation rotate matrix") {
        std::vector<float> alpha_vec = {0, 30, 45, 90, -30, -45, -90};
        std::vector<float> beta_vec = {0, 30, 45, 90, -30, -45, -90};
        std::vector<float> gamma_vec = {0, 30, 45, 90, -30, -45, -90};

        for (int i = 0; i < 5; ++i) {
            Matrix4 res = rotate(alpha_vec[i], beta_vec[i], gamma_vec[i]);
//            glm::mat4 glm_res = glm::rotate(glm::mat4(1.0f), 3.14f, glm::vec3(1.0));
//            compare_matrix(glm_res, res);
        }
    }

    SECTION("Generation lookAt matrix") {
        std::vector<Vector3<float>> my_vectors = {
                Vector3<float>(7.01),
                Vector3<float>(-2),
                Vector3<float>{23.22, -13.09, 9},
                Vector3<float>{3, 36, -425.1},
                Vector3<float>{9.34, 421, -24}
        };

        std::vector<glm::vec3> glm_vectors = {
                glm::vec3(7.01, 7.01, 7.01),
                glm::vec3(-2, -2, -2),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(3, 36, -425.1),
                glm::vec3(9.34, 421, -24)
        };

        for (int i = 0; i < 5; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix4 res = look_at(my_vectors[i], my_vectors[j], Vector3<float>{0, 0, 1});
//                glm::mat4 glm_res = glm::lookAt(glm_vectors[i], glm_vectors[j], glm::vec3(0, 0, 1));
//                compare_matrix(glm_res, res);
            }
        }
    }

    SECTION("Generation perspective matrix") {
        std::vector<float> floats =
                {-53, 1.1414, 23, -4, 7.4, 9, 19.14, 34, 149, 4, -33.2, -34.4, 48.34,
                 50.002, -59.435, 48.1, 3, 48};

        for (int i = 0; i < 16; ++i) {
            for (int j = i + 1; j < 17; ++j) {
                Matrix4 res = perspective(floats[i], floats[j], floats[i + 1], floats[j + 1]);
//                glm::mat4 glm_res = glm::perspective(floats[i], floats[j], floats[i + 1], floats[j + 1]);
//                compare_matrix(glm_res, res);
            }
        }
    }

    SECTION("Generation ortho matrix") {
        std::vector<float>
                floats = {-53, 1.1414, 23, -4, 7.4, 9, 19.14, 34, 149, 4, -33.2, -34.4};

        Matrix4 res = ortho(floats[0], floats[1], floats[2], floats[3], floats[4], floats[5]);
//        glm::mat4 glm_res = glm::transpose(glm::ortho(floats[0],floats[1],floats[2],floats[3],floats[4],floats[5]));
//        compare_matrix(glm_res, res);

        Matrix4 res2 = ortho(floats[6], floats[7], floats[8], floats[9], floats[10], floats[11]);
//        glm::mat4 glm_res2 = glm::transpose(glm::ortho(floats[6],floats[7],floats[8],floats[9],floats[10],floats[11]));
//        compare_matrix(glm_res2, res2);
    }

    SECTION("Output of matrix") {
        Matrix2 mat2{-1.12, 2, 3.002, 4.363};
        Matrix3 mat3{-1.12, 2, 3.002, 4.363, 5, -6, 95, 0.001, -39};
        Matrix4 mat4{-1.12, 2, 3.002, 4.363, 5, -6, 95, 0.001, -39, 5, 0.001, -3, 2, 3.002, 4.363, 5};

        std::ostringstream oss2;
        oss2 << mat2;
        REQUIRE(oss2.str() == "Matrix[size=2x2]: [[-1.12, 2], [3.002, 4.363]]");
        std::ostringstream oss3;
        oss3 << mat3;
        REQUIRE(oss3.str() == "Matrix[size=3x3]: [[-1.12, 2, 3.002], [4.363, 5, -6], [95, 0.001, -39]]");
        std::ostringstream oss4;
        oss4 << mat4;
        REQUIRE(oss4.str() ==
                "Matrix[size=4x4]: [[-1.12, 2, 3.002, 4.363], [5, -6, 95, 0.001], [-39, 5, 0.001, -3], [2, 3.002, 4.363, 5]]");
    }
}