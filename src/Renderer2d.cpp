#include <Renderer2d.h>

#include <shaders.h>
#include <player.h>
#include <resources.h>

extern Player *player;
extern Camera *camera_o;

GLuint _shader_program_2d;

Renderer2d::Renderer2d()
{
    const std::string vertex2d_path = "shaders/vertex2d.glsl", fragment2d_path = "shaders/fragment2d.glsl";
    _shader_program_2d = shader_init(vertex2d_path, fragment2d_path);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer2d::~Renderer2d()
{
    shader_destroy(_shader_program_2d);
}

void Renderer2d::render(std::vector<Entity2D *> *entities)
{
    shader_start(_shader_program_2d);

    GLuint sampler = shader_get_uniform_location(_shader_program_2d, "mysampler");
    shader_load_float(sampler, 0);

    camera_o->update();
    camera_o->load_view_and_projection(_shader_program_2d, "view", "projection");
    GLuint model_location = shader_get_uniform_location(_shader_program_2d, "model");
     
    glEnable(GL_BLEND);

    for(auto i = entities->size(); i-- > 0;)
    {
        Entity2D *current = (*entities)[i];
        shader_load_mat4(model_location, current->get_model());
        current->render();
    }
    
    player->render(model_location);

    shader_stop();
    glDisable(GL_BLEND);
}