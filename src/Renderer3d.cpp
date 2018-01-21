#include <Renderer3d.h>

#include <shaders.h>

Renderer3d::Renderer3d(GLuint shader_program, Camera &camera) : _shader_program(shader_program), _camera(camera)
{

}

Renderer3d::~Renderer3d()
{

}

void Renderer3d::render()
{
    glEnable(GL_CULL_FACE);
    shader_start(_shader_program);

    GLuint sampler = shader_get_uniform_location(_shader_program, "mysampler");
    shader_load_float(sampler, 0);

    _camera.update();
    _camera.load_view_and_projection(_shader_program, "view", "projection");

    GLuint model_location = shader_get_uniform_location(_shader_program, "model");

    for(auto itr = _entities.begin(); itr != _entities.end(); itr++)
    {
        shader_load_mat4(model_location, (*itr)->get_model());
        (*itr)->update();
        (*itr)->render();
    }

    shader_stop();
    glDisable(GL_CULL_FACE);
}

void Renderer3d::add_entity(Entity3D *entity)
{
    _entities.push_back(entity);
}