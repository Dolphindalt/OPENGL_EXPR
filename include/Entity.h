#ifndef ENTITY_H
#define ENTITY_H

#include <model.h>
#include <glm/glm.hpp>
#include <shaders.h>

class Entity
{
public:
    Entity();
    virtual ~Entity();

    void update();
    virtual void render() = 0;

    void set_position(float x, float y, float z);
    void set_position(glm::vec3 nv);
    void set_rotation(float x, float y, float z);
    void set_rotation(glm::vec3 nv);
    void set_scale(float s);
    void set_velocity(float x, float y, float z);
    void set_velocity(glm::vec3 nv);

    glm::vec3 get_position() const;
    glm::vec3 get_rotation() const;
    glm::vec3 get_scale() const;
    glm::vec3 get_velocity() const;
    glm::mat4 get_model() const;
private:
    bool _matrix_needs_update, _velocity_zero;
    glm::vec3 _position, _rotation, _scale;
    glm::vec3 _velocity;
    glm::mat4 _model_matrix;

    void build_model_matrix();
};

class Entity3D : public Entity
{
public:
    Entity3D(TexturedModel &texturedmodel);
    void render();
private:
    TexturedModel _texturedmodel;
};

class Entity2D : public Entity
{
public:
    Entity2D();
    Entity2D(Texture *texture);
    Entity2D(const std::string &texture_path);
    void render();

    void set_texture(Texture *texture);
private:
    Texture *_texture;
};

#endif