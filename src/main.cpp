#include <window.h>
#include <shaders.h>
#include <quad.h>
#include <camera.h>
#include <model.h>
#include <objloader.h>
#include <resources.h>
#include <Entity.h>
#include <glm/gtx/transform.hpp>
#include <Renderer3d.h>

static void init();
static bool gl_init();
static void game_loop();
static void input();
static void update();
static void render();
static void clean();

bool running = true;
GLuint shader_program2d, shader_program3d;
Camera camera;
Entity* dragon;
Renderer3d *renderer3d;

int main()
{
    init();
}

static void init()
{
    window_init();
    gl_init();
    quad_init();
    camera = Camera(PERSPECTIVE, window);
    TexturedModel tm = load_textured_model("assets/fish.obj", "assets/textures/fish.png");
    dragon = new Entity3D(tm);
    dragon->set_velocity(0.2f, 0.0f, 0.0f);
    dragon->set_scale(0.1f);
    renderer3d = new Renderer3d(shader_program3d, camera);
    renderer3d->add_entity(dragon);
    game_loop();
}

static bool gl_init()
{
    bool flag = true;

    const std::string vertex2d_path = "shaders/vertex2d.glsl", fragment2d_path = "shaders/fragment2d.glsl";
    shader_program2d = shader_init(vertex2d_path, fragment2d_path);

    const std::string vertex3d_path = "shaders/vertex3d.glsl", fragment3d_path = "shaders/fragment3d.glsl";
    shader_program3d = shader_init(vertex3d_path, fragment3d_path);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return flag;
}

static void game_loop()
{
    while(running)
    {
        input();

        update();

        render();
    }
    clean();
}

static void input()
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT: running = false; break;
            default: break;
        }
    }
}

static void update()
{
    if(dragon->get_position().x >= 10)
        dragon->set_velocity(-0.2, 0.0, 0.0);
    else if(dragon->get_position().x <= -10)
        dragon->set_velocity(0.2, 0.0, 0.0);
}

static void render()
{
    window.clear();

    renderer3d->render();

    shader_start(shader_program2d); // begin 2d rendering and basic 3d rendering

    /*camera.set_camera_type(ORTHO);
    camera.update();

    camera.getView(view);
    camera.getProjection(projection);
    proj_loc = shader_get_uniform_location(shader_program2d, "projection");
    view_loc = shader_get_uniform_location(shader_program2d, "view");
    shader_load_mat4(proj_loc, projection);
    shader_load_mat4(view_loc, view);

    glm::mat4 model = glm::mat4(1.0f);
    shader_load_mat4(shader_get_uniform_location(shader_program2d, "model"), model);

    quad_render();*/

    shader_stop();

    window.swap_buffer();
}

static void clean()
{
    window_destroy();
    shader_destroy(shader_program2d);
    shader_destroy(shader_program3d);
    quad_destroy();
    delete dragon;
    delete renderer3d;
    naked_model_destroy();
    resources_destroy();
}