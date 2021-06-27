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
#include "libs_project/Objects.hpp"
#include "libs_project/Texture.hpp"
#include "utils/LightningShaderFiller.hpp"
#include "libs_project/VAOObject.hpp"
#include "libs_project/VBOObject.hpp"

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

    std::string s1 = "../res/shaders/directionalLightingShader.vs";
    std::string s2 = "../res/shaders/directionalLightingShader.fs";
    Shader directional(s1, s2);

    std::string s3 = "../res/shaders/pointLightingShader.vs";
    std::string s4 = "../res/shaders/pointLightingShader.fs";
    Shader point(s3, s4);

    std::string s5 = "../res/shaders/spotLightingShader.vs";
    std::string s6 = "../res/shaders/spotLightingShader.fs";
    Shader spot(s5, s6);

    std::string s7 = "../res/shaders/defShader.vs";
    std::string s8 = "../res/shaders/defShader.fs";
    Shader light_cube_shader(s7, s8);

    std::string s9 = "../res/shaders/lighting.vs";
    std::string s10 = "../res/shaders/lighting.fs";
    Shader light(s9, s10);

    Vector3<float> lightPos{1.3f, 1.3f, 1.3f};
    vector<Camera> camera(2);
    int inj = 0;


    ///---------------------------------------------------------------------------------------------
    myVAO cubeVAO;
    myVBO VBO(light_cube, sizeof(light_cube));
    myVAO::link_vertex_attr(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    myVAO::link_vertex_attr(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    myVAO::link_vertex_attr(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));

    ///---------------------------------------------------------------------------------------------

    ///---------------------------------------------------------------------------------------------
    myVAO lightCubeVAO;
    myVAO::link_vertex_attr(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    VBO.bind();
    ///---------------------------------------------------------------------------------------------

    ///---------------------------------------------------------------------------------------------
    myVAO tetraVAO;
    myVAO::link_vertex_attr(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    myVAO::link_vertex_attr(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    VBO.bind();
    ///---------------------------------------------------------------------------------------------

    ///---------------------------------------------------------------------------------------------
    myVAO squareVAO;
    myVAO::link_vertex_attr(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    myVAO::link_vertex_attr(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    VBO.bind();
    ///---------------------------------------------------------------------------------------------

    ///---------------------------Добавление текстур-----------------------------------------------
    unsigned int tex = Texture("../res/img/2.jpg").get_texture_id();
    ///---------------------------------------------------------------------------------------------


    point.LoadLightShaders(0, 1, 32.0f);
    spot.LoadLightShaders(0, 1, 32.0f);
    directional.LoadLightShaders(0, 1, 32.0f);

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

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, tex);

//        addLight(directional, camera[inj], LightSource::DIRECTIONAL);
//        addLight(point, camera[inj], LightSource::POINT);
        addLight(spot, camera[inj], LightSource::SPOT);

        Matrix4 model = Matrix4::identity_matrix();
        Matrix4 view(camera[inj].get_view_matrix());
        Matrix4 projection;
        if (inj == 1) {
            projection = (camera[inj].get_projection_matrix_ortho());
        } else {
            projection = camera[inj].get_projection_matrix_perspective();
        }

        spot.set_mat4("projection", projection);
        spot.set_mat4("view", view);
        spot.set_mat4("model", model);

        Vector3<float> cubePositions[] = {
                Vector3<float>(0.0f, 0.0f, 0.0f),
                Vector3<float>(2.0f, 5.0f, -15.0f),
                Vector3<float>(-1.5f, -2.2f, -2.5f),
                Vector3<float>(-3.8f, -2.0f, -12.3f),
                Vector3<float>(2.4f, -0.4f, -3.5f),
                Vector3<float>(-1.7f, 3.0f, -7.5f),
                Vector3<float>(1.3f, -2.0f, -2.5f),
                Vector3<float>(1.5f, 2.0f, -2.5f),
                Vector3<float>(1.5f, 0.2f, -1.5f),
                Vector3<float>(-1.3f, 1.0f, -1.5f)
        };

        //Other object
        cubeVAO.bind();
        for (unsigned int i = 0; i < 10; i++) {
            Matrix4 transs = transform(cubePositions[i]);
            float angle = 20.0f * i;
            transs = transs * rotate(glm::radians(angle) * 1.0f, glm::radians(angle) * 0.3f,
                                     glm::radians(angle) * 0.5f);
            spot.set_mat4("model", transs);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        light_cube_shader.use();
        light_cube_shader.set_mat4("projection", projection);
        light_cube_shader.set_mat4("view", view);
        model = transform(lightPos);

        light_cube_shader.set_mat4("model", model);
        lightCubeVAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        window.display();
    }

    cubeVAO.delete_array();
    VBO.delete_buffer();

    window.close();
    return 0;
}

#endif //OPENGLENGINE_MAIN_CPP


//        // first object
//        glBindVertexArray(cubeVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        // second object
//        Matrix4 trans1 = transform(Vector3<float>(2 * 0.9f, 0, 0));
//        lighting_shader.set_mat4("model", trans1);
//        glBindVertexArray(tetraVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 12);
//
//        // third object
//        Matrix4 trans2 = transform(Vector3<float>(-2 * 0.9f, 0, 0));
//        lighting_shader.set_mat4("model", trans2);
//        glBindVertexArray(squareVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//
//        // four object
//        Matrix4 trans3 = transform(Vector3<float>(0, -1.0, 0));
//        lighting_shader.set_mat4("model", trans3);
//        glBindVertexArray(lineVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 2);