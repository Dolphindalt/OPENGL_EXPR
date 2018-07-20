#include <Renderer2d.h>

#include <shaders.h>
#include <player.h>
#include <resources.h>

extern Player *player;

Renderer2d::Renderer2d(std::vector<Entity2D *> *entities, Camera &camera) : _camera(camera)
{
    const std::string vertex2d_path = "shaders/vertex2d.glsl", fragment2d_path = "shaders/fragment2d.glsl";
    _shader_program = shader_init(vertex2d_path, fragment2d_path);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _entities = entities;
}

Renderer2d::~Renderer2d()
{
    shader_destroy(_shader_program);
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

    for(auto i = _entities->size(); i-- > 0;)
    {
        Entity2D *current = (*_entities)[i];
        shader_load_mat4(model_location, current->get_model());
        current->render();
    }
    
    player->render(model_location);

    shader_stop();
    glDisable(GL_BLEND);
}