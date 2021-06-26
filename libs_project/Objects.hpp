//
// Created by User on 23.06.2021.
//

#ifndef OPENGLENGINE_SPHEREOBJECT_H
#define OPENGLENGINE_SPHEREOBJECT_H

#include "LightSource.hpp"
#include "../utils/LightningShaderFiller.hpp"

void DrawGrid(float cx, float cz, float step) {

    float _cx = cx / 2;
    float _cz = cz / 2;

    for (float x = -_cx; x <= _cx; x += step) {
//        glBegin(GL_POINTS);
//        glColor3d(0,0,1);
//        glVertex3f(x, -1.0, _cz);
//        glVertex3f(x, -1.0, -_cz);
//        glEnd();
    }

    for (float z = -_cz; z <= _cz; z += step) {
        glBegin(GL_LINES);
        glColor3d(0, 0, 1);
        glVertex2f(_cx, -1.0);
        glVertex2f(_cx, -1.0);
        glEnd();

    }
}

void initgl() {
    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment
    glEnable(GL_POINT_SMOOTH);

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_CULL_FACE);

    // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glDepthMask(GL_TRUE);
    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glDepthRange(0.0f, 1.0f);
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LESS); // Фрагмент будет выводиться, если он находится ближе к камере, чем предыдущий
    glDepthFunc(GL_LEQUAL);
}

inline void push_indices(std::vector<unsigned int> &indices, int sectors, int r, int s) {
    int curRow = r * sectors;
    int nextRow = (r + 1) * sectors;

    indices.push_back(curRow + s);
    indices.push_back(nextRow + s);
    indices.push_back(nextRow + (s + 1));

    indices.push_back(curRow + s);
    indices.push_back(nextRow + (s + 1));
    indices.push_back(curRow + (s + 1));
}

void
createSphere(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices, std::vector<glm::vec2> &texcoords,
             float radius, unsigned int rings, unsigned int sectors) {
    float const R = 1.f / (float) (rings - 1);
    float const S = 1.f / (float) (sectors - 1);

    for (int r = 0; r < rings; ++r) {
        for (int s = 0; s < sectors; ++s) {
            float const y = sin(-M_PI_2 + M_PI * r * R);
            float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
            float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

            texcoords.push_back(glm::vec2(s * S, r * R));
            vertices.push_back(glm::vec3(x, y, z) * radius);
            push_indices(indices, sectors, r, s);
        }
    }
}


void addLight(Shader name_shader, const Camera &camera, LightSource::light_caster_type type) {
    name_shader.use();
    LightSource light(type);
    if (type == LightSource::DIRECTIONAL) {
        light.get_light_source()
                ->set_direction({-0.2f, -1.0f, -0.3f})
                ->set_ambient({0.05f, 0.05f, 0.05f})
                ->set_diffuse({0.5f, 0.5f, 0.5f})
                ->set_specular({0.5f, 0.5f, 0.5f});
    } else if (type == LightSource::POINT) {
        light.get_light_source()
                ->set_position(camera.get_camera_position())
                ->set_ambient({0.2f, 0.2f, 0.2f})
                ->set_diffuse({1.0f, 1.0f, 1.0f})
                ->set_specular({1.0f, 1.0f, 1.0f})
                ->set_constant(1.0f)
                ->set_linear(0.09f)
                ->set_quadratic(0.032f);
    } else {
        light.get_light_source()
                ->set_position(camera.get_camera_position())
                ->set_direction(camera.get_camera_front())
                ->set_cut_off(glm::cos(glm::radians(15.0f)))
                ->set_outer_cut_off(glm::cos(glm::radians(23.0f)))
                ->set_ambient({0.1f, 0.1f, 0.1f})
                ->set_diffuse({0.8f, 0.8f, 0.8f})
                ->set_specular({1.0f, 1.0f, 1.0f})
                ->set_constant(1.0f)
                ->set_linear(0.09f)
                ->set_quadratic(0.032f);
    }
    LightningShaderFiller::fill_light_shader(name_shader, light);
}

[[maybe_unused]] float lines[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0, 0.0f
};

[[maybe_unused]] float square[] = {
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
};

[[maybe_unused]] float cube[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

[[maybe_unused]] float light_cube[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

[[maybe_unused]] float tetra[] = {
        //нижний
        0.0f, 0.0f, 0.0f, 0.25f, 0.43f,
        0.86f, 0.0f, 0.0f, 0.5f, 0.0f,
        0.43f, 0.86f, 0.0f, 0.75f, 0.43f,
        //задний
        0.0f, 0.0f, 0.0f, 0.26f, 0.43f,
        0.43f, 0.86f, 0.0f, 0.75f, 0.43f,
        0.43f, 0.43f, 0.43f, 0.5f, 0.86f,
        //правый
        0.86f, 0.0f, 0.0f, 0.5f, 0.0f,
        0.43f, 0.86f, 0.0f, 0.75f, 0.43f,
        0.43f, 0.43f, 0.43f, 1.0f, 0.0f,
        //левый
        0.0f, 0.0f, 0.0f, 0.25f, 0.43f,
        0.86f, 0.0f, 0.0f, 0.5f, 0.0f,
        0.43f, 0.43f, 0.43f, 0.0f, 0.0f
};

#endif //OPENGLENGINE_SPHEREOBJECT_H
