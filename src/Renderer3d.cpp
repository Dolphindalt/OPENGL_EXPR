#include <Renderer3d.h>

#include <shaders.h>

GLuint _shader_program_3d;
extern Camera *camera_p;

Renderer3d::Renderer3d()
{
    const std::string vertex3d_path = "shaders/vertex3d.glsl", fragment3d_path = "shaders/fragment3d.glsl";
    _shader_program_3d = shader_init(vertex3d_path, fragment3d_path);
}

Renderer3d::~Renderer3d()
{
    shader_destroy(_shader_program_3d);
}

void Renderer3d::render(std::vector<Entity3D *> *entities)
{
    glEnable(GL_CULL_FACE);
    shader_start(_shader_program_3d);

    GLuint sampler = shader_get_uniform_location(_shader_program_3d, "mysampler");
    shader_load_float(sampler, 0);

    camera_p->update();
    camera_p->load_view_and_projection(_shader_program_3d, "view", "projection");

    GLuint model_location = shader_get_uniform_location(_shader_program_3d, "model");

    for(auto i = entities->size(); i-- > 0;)
    {
        Entity3D *current = (*entities)[i];
        shader_load_mat4(model_location, current->get_model());
        current->render();
    }

    shader_stop();
    glDisable(GL_CULL_FACE);
}