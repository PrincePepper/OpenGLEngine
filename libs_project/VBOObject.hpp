//
// Created by User on 27.06.2021.
//

#ifndef OPENGLENGINE_VBOOBJECT_HPP
#define OPENGLENGINE_VBOOBJECT_HPP

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class myVBO {
public:
    explicit myVBO(float *vertices, size_t vertices_size) {
        glGenBuffers(1, &ID);
        bind();
        glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
    };

    void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    };

    void delete_buffer() {
        glDeleteBuffers(1, &ID);
    }

private:
    unsigned int ID{};
};

#endif //OPENGLENGINE_VBOOBJECT_HPP
