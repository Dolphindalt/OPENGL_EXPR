#include <Renderer3d.h>

#include <shaders.h>

Renderer3d::Renderer3d(std::vector<Entity3D *> *entities, Camera &camera) : _camera(camera)
{
    const std::string vertex3d_path = "shaders/vertex3d.glsl", fragment3d_path = "shaders/fragment3d.glsl";
    _shader_program = shader_init(vertex3d_path, fragment3d_path);
    _entities = entities;
}

Renderer3d::~Renderer3d()
{
    shader_destroy(_shader_program);
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

    for(auto i = _entities->size(); i-- > 0;)
    {
        Entity3D *current = (*_entities)[i];
        shader_load_mat4(model_location, current->get_model());
        current->render(model_location);
    }

    shader_stop();
    glDisable(GL_CULL_FACE);
}