#include <Renderer2d.h>

#include <shaders.h>

Renderer2d::Renderer2d(GLuint shader_program, Camera &camera) : _shader_program(shader_program), _camera(camera)
{

}

Renderer2d::~Renderer2d()
{

}

void Renderer2d::render()
{
    shader_start(_shader_program);

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
}