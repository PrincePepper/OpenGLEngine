#pragma once

#include "shaderLoader.hpp"
#include <GL/glew.h>
#include "../libs/glm/glm/glm.hpp"
#include "../libs_project/Matrix.hpp"

class Shader {
public:
    Shader(std::string &vertex_path, std::string &fragment_path) {
        shader_id = LoadShaders(vertex_path, fragment_path);
    }

    void use() const {
        glUseProgram(shader_id);
    }

    void set_mat4(const GLchar *name, const Matrix4 &data) const {
        std::vector<float> glm_matrix = matrix_to_glm(data);
        glUniformMatrix4fv(glGetUniformLocation(shader_id, name), 1, GL_FALSE, &glm_matrix[0]);
    }

private:
    GLuint shader_id;

    static std::vector<float> matrix_to_glm(const Matrix4 &data) {
        return {
                data[0][0], data[0][1], data[0][2], data[0][3],
                data[1][0], data[1][1], data[1][2], data[1][3],
                data[2][0], data[2][1], data[2][2], data[2][3],
                data[3][0], data[3][1], data[3][2], data[3][3]
        };
    }

};