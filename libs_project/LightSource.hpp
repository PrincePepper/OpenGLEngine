//
// Created by User on 26.06.2021.
//

#ifndef OPENGLENGINE_LIGHTSOURCE_HPP
#define OPENGLENGINE_LIGHTSOURCE_HPP

#include <limits>

class LightSource {
public:
    enum light_caster_type {
        DIRECTIONAL,
        POINT,
        SPOT,
    };

    explicit LightSource(light_caster_type _type) : type(_type) {}

    LightSource *get_light_source() {
        return this;
    }

    [[nodiscard]] light_caster_type get_type() const {
        return type;
    };

    LightSource *set_direction(const Vector3<float> &_direction) {
        direction = _direction;
        return this;
    };

    [[nodiscard]] Vector3<float> get_direction() const {
        return direction;
    };

    LightSource *set_ambient(const Vector3<float> &_ambient) {
        ambient = _ambient;
        return this;
    };

    [[nodiscard]] Vector3<float> get_ambient() const {
        return ambient;
    };

    LightSource *set_diffuse(const Vector3<float> &_diffuse) {
        diffuse = _diffuse;
        return this;
    };

    [[nodiscard]] Vector3<float> get_diffuse() const {
        return diffuse;
    };

    LightSource *set_specular(const Vector3<float> &_specular) {
        specular = _specular;
        return this;
    };

    [[nodiscard]] Vector3<float> get_specular() const {
        return specular;
    };

    LightSource *set_position(const Vector3<float> &_position) {
        position = _position;
        return this;
    };

    [[nodiscard]] Vector3<float> get_position() const {
        return position;
    };

    LightSource *set_constant(float _constant) {
        constant = _constant;
        return this;
    };

    [[nodiscard]] float get_constant() const {
        return constant;
    };

    LightSource *set_linear(float _linear) {
        linear = _linear;
        return this;
    };

    [[nodiscard]] float get_linear() const {
        return linear;
    };

    LightSource *set_quadratic(float _quadratic) {
        quadratic = _quadratic;
        return this;
    };

    [[nodiscard]] float get_quadratic() const {
        return quadratic;
    };

    LightSource *set_cut_off(float _cut_off) {
        cut_off = _cut_off;
        return this;
    };

    [[nodiscard]] float get_cut_off() const {
        return cut_off;
    };

    LightSource *set_outer_cut_off(float _outer_cut_off) {
        outer_cut_off = _outer_cut_off;
        return this;
    };

    [[nodiscard]] float get_outer_cut_off() const {
        return outer_cut_off;
    };

    [[nodiscard]] size_t get_point_index() const {
        return point_index;
    }

    LightSource *set_point_index(size_t _point_index) {
        point_index = _point_index;
        return this;
    }

private:
    light_caster_type type = DIRECTIONAL;

    size_t point_index = 0;

    Vector3<float> direction{};
    Vector3<float> ambient{};
    Vector3<float> diffuse{};
    Vector3<float> specular{};
    Vector3<float> position{};

    float constant = std::numeric_limits<float>::min();
    float linear = std::numeric_limits<float>::min();
    float quadratic = std::numeric_limits<float>::min();
    float cut_off = std::numeric_limits<float>::min();
    float outer_cut_off = std::numeric_limits<float>::min();
};


#endif //OPENGLENGINE_LIGHTSOURCE_HPP
