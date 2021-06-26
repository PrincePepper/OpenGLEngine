#ifndef OPENGLENGINE_MAIN_CPP
#define OPENGLENGINE_MAIN_CPP

#include <iostream>
#include <vector>

#include <GL/glew.h>

#include <SFML/Window.hpp>

#include "libs/stb/stb_image.h"

#include "utils/shaderLoader.hpp"
#include "libs_project/Camera.hpp"
#include "utils/Shader.hpp"
#include "libs_project/Objects.h"

using namespace std;

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24; // количество битов буффера глубины
    settings.stencilBits = 8; //количество битов буфера трафарета
    settings.majorVersion = 4;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Core;

    sf::Window window(sf::VideoMode(1800, 1080, 32), "First Window",
                      sf::Style::Titlebar | sf::Style::Close, settings);
    window.setMouseCursorVisible(false); // отсключить указатель мышки

    glewExperimental = GL_TRUE; // включить все современные функции ogl
    initgl();
    if (GLEW_OK != glewInit()) { // включить glew
        cout << "Error:: glew not init =(" << endl;
        return -1;
    }

    std::string s1 = "../res/shaders/lighting.vs";
    std::string s2 = "../res/shaders/lighting.fs";
    Shader lighting_shader(s1, s2);

    std::string s3 = "../res/shaders/def_shader.vs";
    std::string s4 = "../res/shaders/def_shader.fs";
    Shader light_cube_shader(s3, s4);

    Vector3<float> lightPos{2.0f, 1.0f, 1.0f};
    vector<Camera> camera(2);
    int inj = 0;

    ///---------------------------------------------------------------------------------------------
    unsigned int VBO, EBO, cubeVAO, tetraVAO, squareVAO, sphereVAO, lineVAO, lightCubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(light_cube), light_cube, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    ///---------------------------------------------------------------------------------------------

    ///---------------------------------------------------------------------------------------------
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    ///---------------------------------------------------------------------------------------------

    ///---------------------------------------------------------------------------------------------
    glGenVertexArrays(1, &tetraVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(tetraVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tetra), tetra, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    ///---------------------------------------------------------------------------------------------

    ///---------------------------------------------------------------------------------------------
    glGenVertexArrays(1, &squareVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(squareVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    ///---------------------------------------------------------------------------------------------

    ///---------------------------------------------------------------------------------------------
    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(lineVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lines), lines, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    ///---------------------------------------------------------------------------------------------

    ///---------------------------Добавление текстур-----------------------------------------------
    unsigned int texture;
    createTexture(texture, "../res/img/2.jpg");
    ///---------------------------------------------------------------------------------------------

    bool isGo = true;

    while (isGo) {
        sf::Event window_event{};
        while (window.pollEvent(window_event)) {
            switch (window_event.type) {
                case sf::Event::Closed:
                    isGo = false;
                    break;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                        if (inj == 0) inj = 1;
                        else inj = 0;
                    }
                    camera[inj].keyboard_input();
                    break;
                case sf::Event::MouseMoved:
                    camera[inj].mouse_input(window, window_event.mouseMove.x, window_event.mouseMove.y);
                    break;
                case sf::Event::MouseWheelMoved:
                    camera[inj].scroll_callback(window, window_event.mouseWheelScroll.x,
                                                window_event.mouseWheel.y); //надо пофиксить
                    break;
                default:
                    break;
            }
        }


        glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Matrix4 model = Matrix4::identity_matrix();
        Matrix4 view(camera[inj].get_view_matrix());
        Matrix4 projection;
        if (inj == 1) {
            projection = (camera[inj].get_projection_matrix_ortho());
            cout << "ortho camera" << endl;
        } else {
            projection = camera[inj].get_projection_matrix_perspective();
            cout << "perspective camera" << endl;
        }

        lighting_shader.use();
        lighting_shader.set_vec3("objectColor", Vector3<float>(0.0f, 1.0f, 0.0f));
        lighting_shader.set_vec3("lightColor", Vector3<float>(1.0f, 1.0f, 1.0f));
        lighting_shader.set_vec3("lightPos", lightPos);
        lighting_shader.set_vec3("viewPos", camera[inj].get_camera_position());
        lighting_shader.set_mat4("projection", projection);
        lighting_shader.set_mat4("view", view);
        lighting_shader.set_mat4("model", model);

        // first object
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // second object
        Matrix4 trans1 = transform(Vector3<float>(2 * 0.9f, 0, 0));
        lighting_shader.set_mat4("model", trans1);
        glBindVertexArray(tetraVAO);
        glDrawArrays(GL_TRIANGLES, 0, 12);

        // third object
        Matrix4 trans2 = transform(Vector3<float>(-2 * 0.9f, 0, 0));
        lighting_shader.set_mat4("model", trans2);
        glBindVertexArray(squareVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // four object
        Matrix4 trans3 = transform(Vector3<float>(0, -1.0, 0));
        lighting_shader.set_mat4("model", trans3);
        glBindVertexArray(lineVAO);
        glDrawArrays(GL_TRIANGLES, 0, 2);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, texture);

        light_cube_shader.use();
        light_cube_shader.set_mat4("projection", projection);
        light_cube_shader.set_mat4("view", view);
        model = transform(lightPos);

        light_cube_shader.set_mat4("model", model);
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        window.display();
    }

    window.close();
    return 0;
}

#endif //OPENGLENGINE_MAIN_CPP