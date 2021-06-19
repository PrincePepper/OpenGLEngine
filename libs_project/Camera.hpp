#pragma once

#ifndef OPENGLENGINE_CAMERA_HPP
#define OPENGLENGINE_CAMERA_HPP

#include <SFML/Window.hpp>
#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"

#include "Matrix.hpp"

class Camera {
public:
    Camera() : camera_position(3), camera_front(3), camera_up(3) {
        camera_position = Vector3<float>{0.0, 0.0, 3.0};
        camera_front = Vector3<float>{0.0, 0.0, -1.0};
        camera_up = Vector3<float>{0.0, 1.0, 0.0};
    }

    Matrix4 get_view_matrix() {
        return look_at(camera_position, camera_position + camera_front, camera_up);
    }

    static Matrix4 get_projection_matrix() {
        return perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    }

    void keyboard_input() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            camera_position += camera_front * speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            Vector3<float> crossResult(cross(camera_front, camera_up));
            camera_position -= crossResult.normalize() * speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            Vector3<float> crossResult(cross(camera_front, camera_up));
            camera_position += crossResult.normalize() * speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            camera_position -= camera_front * speed;
        }
    }

    void mouse_input(sf::Window &window, float x_pos, float y_pos) {
        if (firstMouse) {
            lastX = x_pos;
            lastY = y_pos;
            firstMouse = false;
        }

        float x_offset = x_pos - lastX;
        float y_offset = lastY - y_pos;
        lastX = x_pos;
        lastY = y_pos;

        x_offset *= speed;
        y_offset *= speed;

        yaw += x_offset;
        pitch += y_offset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }

        if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        Vector3<float> front;
        front[0] = static_cast<float>(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
        front[1] = static_cast<float>(sin(glm::radians(pitch)));
        front[2] = static_cast<float>(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
        camera_front = front.normalize();
    }

    [[nodiscard]] int getIdCam() const {
        return id_cam;
    }

    void setIdCam(int idCam) {
        id_cam = idCam;
    }

private:
    Vector3<float> camera_position;
    Vector3<float> camera_front;
    Vector3<float> camera_up;

    float speed = 0.2;

    float yaw = -90.0;
    float pitch = 0.0;
    bool firstMouse = true;

    int id_cam = 0;

    float lastX;
    float lastY;
};

#endif //OPENGLENGINE_ЫВ_H