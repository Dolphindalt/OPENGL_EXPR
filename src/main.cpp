#include <window.h>
#include <shaders.h>
#include <quad.h>
#include <cube.h>
#include <camera.h>

#include <glm/gtx/transform.hpp>

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
    cube_init();
    camera = Camera(ORTHO, window);
    game_loop();
}

static bool gl_init()
{
    bool flag = true;

    std::string vertex2d_path = "shaders/vertex2d.glsl", fragment2d_path = "shaders/fragment2d.glsl";
    shader_program = shader_init(vertex2d_path, fragment2d_path);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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

    glm::mat4 mvp;

    shader_start(shader_program);
    camera.set_camera_type(PERSPECTIVE);
    camera.update();
    camera.getMVP(mvp);
    shader_load_mat4(shader_get_uniform_location(shader_program, "MVP"), mvp);
    glm::mat4 model = glm::mat4(1.0f);
    model = model * glm::rotate(glm::radians(45.0f), glm::vec3(0, 1, 1));
    shader_load_mat4(shader_get_uniform_location(shader_program, "model"), model);

    cube_render();

    camera.set_camera_type(ORTHO);
    camera.update();
    camera.getMVP(mvp);
    shader_load_mat4(shader_get_uniform_location(shader_program, "MVP"), mvp);
    model = glm::mat4(1.0f);
    shader_load_mat4(shader_get_uniform_location(shader_program, "model"), model);

    quad_render();

    shader_stop();
    window.swap_buffer();
}

static void clean()
{
    window_destroy();
    shader_destroy(shader_program);
    quad_destroy();
    cube_destroy();
}