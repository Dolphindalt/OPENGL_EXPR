#include <window.h>
#include <shaders.h>
#include <quad.h>
#include <cube.h>
#include <camera.h>
#include <model.h>
#include <objloader.h>

#include <glm/gtx/transform.hpp>

static void init();
static bool gl_init();
static void game_loop();
static void input();
static void render();
static void clean();

bool running = true;
GLuint shader_program2d, shader_program3d;
Camera camera;
NakedModel dragon;

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
    dragon = load_model("assets/dragon.obj");
    game_loop();
}

static bool gl_init()
{
    bool flag = true;

    std::string vertex2d_path = "shaders/vertex2d.glsl", fragment2d_path = "shaders/fragment2d.glsl";
    shader_program2d = shader_init(vertex2d_path, fragment2d_path);

    std::string vertex3d_path = "shaders/vertex3d.glsl", fragment3d_path = "shaders/fragment3d.glsl";
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

    shader_start(shader_program3d); // advanced 3d shaders

    camera.set_camera_type(PERSPECTIVE);
    camera.update();
    camera.getMVP(mvp);
    shader_load_mat4(shader_get_uniform_location(shader_program3d, "MVP"), mvp);
    glm::mat4 model = glm::mat4(1.0f);
    shader_load_mat4(shader_get_uniform_location(shader_program3d, "model"), model);

    naked_model_render(dragon);

    shader_stop();

    shader_start(shader_program2d); // begin 2d rendering and basic 3d rendering
    camera.set_camera_type(PERSPECTIVE);
    camera.update();
    camera.getMVP(mvp);
    shader_load_mat4(shader_get_uniform_location(shader_program2d, "MVP"), mvp);
    model = glm::mat4(1.0f);
    model = model * glm::rotate(glm::radians(45.0f), glm::vec3(0, 1, -1));
    model = glm::translate(model, glm::vec3(0, 5, 5));
    shader_load_mat4(shader_get_uniform_location(shader_program2d, "model"), model);

    cube_render();

    camera.set_camera_type(ORTHO);
    camera.update();
    camera.getMVP(mvp);
    shader_load_mat4(shader_get_uniform_location(shader_program2d, "MVP"), mvp);
    model = glm::mat4(1.0f);
    shader_load_mat4(shader_get_uniform_location(shader_program2d, "model"), model);

    //quad_render();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
    shader_load_mat4(shader_get_uniform_location(shader_program2d, "model"), model);

    quad_render();

    shader_stop();

    window.swap_buffer();
}

static void clean()
{
    window_destroy();
    shader_destroy(shader_program2d);
    shader_destroy(shader_program3d);
    quad_destroy();
    cube_destroy();
    naked_model_destroy();
}