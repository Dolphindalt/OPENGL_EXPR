#include <Entity.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <quad.h>
#include <resources.h>

Entity::Entity() : _matrix_needs_update(true), _velocity_zero(true), _position(glm::vec3(0.0f)), _rotation(glm::vec3(0.0f)), _scale(glm::vec3(1.0f)), _velocity(glm::vec3(0.0f))
{
    build_model_matrix();
}

Entity::~Entity()
{

}

void Entity::update()
{
    if(!_velocity_zero) _matrix_needs_update = true;
    if(_matrix_needs_update)
    {
        build_model_matrix();
    }
}

void Entity::build_model_matrix()
{
    _position += _velocity;

    _model_matrix = glm::mat4(1.0f);

    _model_matrix = _model_matrix * glm::scale(_scale);

    _model_matrix = _model_matrix * glm::rotate(_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    _model_matrix = _model_matrix * glm::rotate(_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    _model_matrix = _model_matrix * glm::rotate(_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    _model_matrix = _model_matrix * glm::translate(_position);

    _matrix_needs_update = false;
}

void Entity::set_position(float x, float y, float z)
{
    _position = glm::vec3(x, y, z);
    _matrix_needs_update = true;
}

void Entity::set_position(glm::vec3 nv)
{
    _position = nv;
    _matrix_needs_update = true;
}

void Entity::set_rotation(float x, float y, float z)
{
    _rotation = glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z));
}

void Entity::set_rotation(glm::vec3 nv)
{
    _rotation = nv;
}

void Entity::set_scale(float s)
{
    _scale = glm::vec3(s, s, s);
    _matrix_needs_update = true;
}

void Entity::set_velocity(float x, float y, float z)
{
    _velocity_zero = (x == 0 && y == 0 && z == 0) ? true : false;
    _velocity = glm::vec3(x, y, z);
    _matrix_needs_update = true;
}

void Entity::set_velocity(glm::vec3 nv)
{
    _velocity_zero = (nv == glm::vec3(0.0f, 0.0f, 0.0f)) ? true : false;
    _velocity = nv;
    _matrix_needs_update = true;
}

glm::vec3 Entity::get_position() const 
{
    return _position;
}

glm::vec3 Entity::get_rotation() const
{
    return _rotation;
}

glm::vec3 Entity::get_scale() const
{
    return _scale;
}

glm::vec3 Entity::get_velocity() const
{
    return _velocity;
}

glm::mat4 Entity::get_model() const
{
    return _model_matrix;
}

// BEGIN ENTITY3D

Entity3D::Entity3D(TexturedModel &texturedmodel) : Entity(), _texturedmodel(texturedmodel)
{

}

void Entity3D::render()
{
    textured_model_render(_texturedmodel);
}

// BEGIN ENTITY2D

Entity2D::Entity2D() : Entity()
{

}

Entity2D::Entity2D(Texture *texture) : Entity(), _texture(texture)
{

}

Entity2D::Entity2D(const std::string &texture_path) : Entity()
{
    _texture = get_texture(texture_path);
}

void Entity2D::render()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture->texture_id);
    quad_render();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Entity2D::set_texture(Texture *texture)
{
    _texture = texture;
}