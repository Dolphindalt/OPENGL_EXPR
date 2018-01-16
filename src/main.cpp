#include <window.h>
#include <shaders.h>
#include <square.h>
#include <camera.h>

static void init();
static bool gl_init();
static void game_loop();
static void input();
static void render();
static void clean();

bool running = true;
GLuint shader_program;
Camera camera;

int main()
{
    init();
}

static void init()
{
    window_init();
    gl_init();
    quad_init();
    camera = Camera(ORTHO, window);
    game_loop();
}

static bool gl_init()
{
    bool flag = true;

    std::string vertex2d_path = "shaders/vertex2d.glsl", fragment2d_path = "shaders/fragment2d.glsl";
    shader_program = shader_init(vertex2d_path, fragment2d_path);

    return flag;
}

static void game_loop()
{
    while(running)
    {
        input();

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

static void render()
{
    window.clear();
    camera.update();
    shader_start(shader_program);
    glm::mat4 mvp;
    camera.getMVP(mvp);
    shader_load_mat4(shader_get_uniform_location(shader_program, "MVP"), mvp);

    quad_render();

    shader_stop();
    window.swap_buffer();
}

static void clean()
{
    window_destroy();
    shader_destroy(shader_program);
    quad_destroy();
}