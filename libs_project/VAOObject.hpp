//
// Created by User on 27.06.2021.
//

#ifndef OPENGLENGINE_VAOOBJECT_HPP
#define OPENGLENGINE_VAOOBJECT_HPP

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class myVAO {
public:
    myVAO() {
        glGenVertexArrays(1, &ID);
        bind();
    };

    static void link_vertex_attr(GLuint attribute_idx,
                                 GLint size,
                                 GLenum type,
                                 GLboolean is_normalise,
                                 GLsizei stride,
                                 const GLvoid *pointer) {
        glVertexAttribPointer(attribute_idx, size, type, is_normalise, stride, pointer);
        glEnableVertexAttribArray(attribute_idx);
    };

    void bind() const {
        glBindVertexArray(ID);
    };

    void delete_array() const {
        glDeleteVertexArrays(1, &ID);
    }

private:
    unsigned int ID{};
};

#endif //OPENGLENGINE_VAOOBJECT_HPP
