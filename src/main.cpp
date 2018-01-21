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
#include <Renderer2d.h>

static void init();
static bool gl_init();
static void game_loop();
static void input();
static void update();
static void render();
static void clean();

bool running = true;
GLuint shader_program2d, shader_program3d;
Camera camera_p, camera_o;
Entity3D *dragon;
Entity2D *grass, *grass2;
Renderer3d *renderer3d;
Renderer2d *renderer2d;

int main()
{
    init();
}

static void init()
{
    window_init();
    window.set_clear_color(0.1, 0.3, 0.7, 1.0);
    gl_init();
    quad_init();
    camera_p = Camera(PERSPECTIVE, window);
    camera_o = Camera(ORTHO, window);

    TexturedModel tm = load_textured_model("assets/fish.obj", "assets/textures/fish.png");
    dragon = new Entity3D(tm);
    dragon->set_velocity(0.5f, 0.0f, 0.0f);
    dragon->set_scale(0.1f);

    renderer3d = new Renderer3d(shader_program3d, camera_p);
    renderer3d->add_entity(dragon);

    grass = new Entity2D("assets/textures/grass.png");
    grass->set_position(-1.0f, -1.0f, 0.0f);
    grass2 = new Entity2D("assets/textures/grass.png");
    grass2->set_position(0.0, -1.0f, 0.0);

    renderer2d = new Renderer2d(shader_program2d, camera_o);
    renderer2d->add_entity(grass);
    renderer2d->add_entity(grass2);

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
    if(dragon->get_position().x >= 30)
    {
        dragon->set_velocity(-0.5, 0.0, 0.0);
        dragon->set_rotation(0.0, 90.0, 0.0);
    }
    else if(dragon->get_position().x <= -30)
    {
        dragon->set_velocity(0.5, 0.0, 0.0);
        dragon->set_rotation(0.0, 0.0, 0.0);
    }
}

static void render()
{
    window.clear();

    renderer3d->render();

    renderer2d->render();

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
    delete grass;
    delete grass2;
    naked_model_destroy();
    resources_destroy();
}