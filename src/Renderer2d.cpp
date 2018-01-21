#include <Renderer2d.h>

#include <shaders.h>

Renderer2d::Renderer2d(GLuint shader_program, Camera &camera) : _shader_program(shader_program), _camera(camera)
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer2d::~Renderer2d()
{

}

void Renderer2d::render()
{
    shader_start(_shader_program);

    GLuint sampler = shader_get_uniform_location(_shader_program, "mysampler");
    shader_load_float(sampler, 0);

    _camera.update();
    _camera.load_view_and_projection(_shader_program, "view", "projection");
    GLuint model_location = shader_get_uniform_location(_shader_program, "model");
     
    glEnable(GL_BLEND);

    for(auto itr = _entities.begin(); itr != _entities.end(); itr++)
    {
        shader_load_mat4(model_location, (*itr)->get_model());
        (*itr)->update();
        (*itr)->render();
    }

    glDisable(GL_BLEND);

    shader_stop();
}

void Renderer2d::add_entity(Entity2D *entity)
{
    _entities.push_back(entity);
}