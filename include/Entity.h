#ifndef ENTITY_H
#define ENTITY_H

#include <model.h>
#include <glm/glm.hpp>

class Entity
{
public:
    Entity(TexturedModel &model);
    ~Entity();

    void update();
    void render();

    void set_scale(float s);
    void set_velocity(float x, float y, float z);
    void set_velocity(glm::vec3 nv);

    glm::vec3 get_position() const;
    glm::vec3 get_rotation() const;
    glm::vec3 get_scale() const;
    glm::vec3 get_velocity() const;
    glm::mat4 get_model() const;
private:
    TexturedModel _model;
    bool _matrix_needs_update, _velocity_zero;
    glm::vec3 _position, _rotation, _scale;
    glm::vec3 _velocity;
    glm::mat4 _model_matrix;

    void build_model_matrix();
};

#endif