//
// Created by User on 26.06.2021.
//

#ifndef OPENGLENGINE_TEXTURE_HPP
#define OPENGLENGINE_TEXTURE_HPP

#include <functional>

class Texture {
public:
    explicit Texture(char const *path) {
        glGenTextures(1, &texture_id);

        int width, height, nr_channels;
        unsigned char *data = stbi_load(path, &width, &height, &nr_channels, 0);
        if (data) {
            GLenum format;
            switch (nr_channels) {
                case 1:
                    format = GL_RED;
                    break;
                case 3:
                    format = GL_RGB;
                    break;
                case 4:
                    format = GL_RGBA;
                    break;
                default:
                    format = 0;
            }
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
            return;
        }

        std::cout << " Texture failed to load at path (texture): " << path << std::endl;
        stbi_image_free(data);
    };

    [[nodiscard]] unsigned int get_texture_id() const {
        return texture_id;
    }

    void set_texture_id(unsigned int tex_id) {
        texture_id = tex_id;
    }

    std::string get_texture_path() const {
        return path;
    }

    void set_texture_path(std::string &tex_path) {
        path = tex_path;
    }

private:
    unsigned int texture_id = -1;
    std::string path;
};

#endif //OPENGLENGINE_TEXTURE_HPP
