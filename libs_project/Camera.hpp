//
// Created by User on 14.06.2021.
//

#ifndef OPENGLENGINE_CAMERA_HPP
#define OPENGLENGINE_CAMERA_HPP

#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    static Matrix4 get_view_matrix_without_translation() {
        Matrix4 result = look_at(camera_position, camera_position + camera_front, camera_up);
        result[3][0] = 0;
        result[3][1] = 0;
        result[3][2] = 0;
        result[3][3] = 1;

        return result;
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
            last_x = x_pos;
            last_y = y_pos;
            firstMouse = false;
        }

        float x_offset = x_pos - last_x;
        float y_offset = last_y - y_pos;
        last_x = x_pos;
        last_y = y_pos;

        x_offset *= speed;
        y_offset *= speed;

        yaw += x_offset;
        pitch += y_offset;

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

    const Vector3<float> &get_camera_position() const {
        return camera_position;
    }

    const Vector3<float> &get_camera_front() const {
        return camera_front;
    }

    const Vector3<float> &get_camera_up() const {
        return camera_up;
    }

private:
    Vector3<float> camera_position;
    Vector3<float> camera_front;
    Vector3<float> camera_up;

    float speed = 0.2;

    float yaw = -90.0;
    float pitch = 0.0;
    bool firstMouse = true;

    float last_x;
    float last_y;
};

#endif //OPENGLENGINE_CAMERA_HPP