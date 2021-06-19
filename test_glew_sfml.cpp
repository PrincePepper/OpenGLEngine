#ifndef OPENGLENGINE_MAIN_CPP
#define OPENGLENGINE_MAIN_CPP

#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>

#include "libs/stb/stb_image.h"

#include "utils/shaderLoader.hpp"
#include "libs_project/Camera.hpp"
#include "utils/Shader.hpp"

using namespace std;

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24; // количество битов буффера глубины
    settings.stencilBits = 8; //количество битов буфера трафарета
    settings.majorVersion = 4;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Core;

    sf::Window window(sf::VideoMode(1200, 900, 32), "First Window",
                      sf::Style::Titlebar | sf::Style::Close);

    glewExperimental = GL_TRUE; // включить все современные функции ogl

    glEnable(GL_DEPTH_TEST);

    if (GLEW_OK != glewInit()) { // включить glew
        cout << "Error:: glew not init =(" << endl;
        return -1;
    }

    std::string s1 = "../res/shaders/e4.vs";
    std::string s2 = "../res/shaders/e4.fs";
    Shader my_shader(s1, s2);

    std:
    vector<Camera> camera(2);
    int inj = 0;
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nr_channels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load("../res/img/2.jpg", &width, &height, &nr_channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    bool isGo = true;

    while (isGo) {
        sf::Event window_event{};
        while (window.pollEvent(window_event)) {
            switch (window_event.type) {
                case sf::Event::Closed:
                    isGo = false;
                    break;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                        if (inj == 0)
                            inj = 1;
                        else inj = 0;
                    camera[inj].keyboard_input();
                    break;
                case sf::Event::MouseMoved:
                    camera[inj].mouse_input(window, window_event.mouseMove.x, window_event.mouseMove.y);
                    break;
                default:
                    break;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

        my_shader.use();

        glBindVertexArray(VAO);

        Matrix4 model = Matrix4::identity_matrix();
        Matrix4 view(camera[inj].get_view_matrix());
        Matrix4 projection(Camera::get_projection_matrix());

        my_shader.set_mat4("model", model);
        my_shader.set_mat4("view", view);
        my_shader.set_mat4("projection", projection);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        window.display();
    }

    window.close();
    return 0;
}

#endif //OPENGLENGINE_MAIN_CPP