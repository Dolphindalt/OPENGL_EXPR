#include <main.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <window.h>
#include <GameState.h>
#include <event.h>
#include <shaders.h>
#include <quad.h>
#include <camera.h>
#include <glm/gtx/transform.hpp>

#include <cassert>

static void init();
static bool gl_init();
static void game_loop();
static void clean();

#define TICK_INTERVAL 60.0

bool running = true;
Camera *camera_p, *camera_o;

extern GameState *currentState;

int main(int argc, char *argv[])
{
    init();
}

static void init()
{
    window_init();
    window.set_clear_color(0.1, 0.3, 0.7, 1.0);
    gl_init();
    quad_init();
    camera_o = new Camera(ORTHO, window);
    camera_p = new Camera(PERSPECTIVE, window);
    init_gamestates();

    switchToState(0);

    game_loop();
}

static bool gl_init()
{
    bool flag = true;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return flag;
}

static void game_loop()
{
    double delta = 0;
    Uint64 last_time = SDL_GetPerformanceCounter();
    double amount_of_ticks = 60.0;
    double ns = 1000000000.0 / amount_of_ticks;
    Uint32 timer = SDL_GetTicks();
    int frames = 0;
    while(running)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        delta += (now - last_time) / ns;
        last_time = now;

        while(delta >= 1.0) 
        {
            handle_input(running);
            currentState->update(delta);
            delta--;
        }

        window.clear();
        currentState->render();
        window.swap_buffer();

        frames++;
        if(SDL_GetTicks() - timer > 1000)
        {
            timer += 1000;
            frames = 0;
        }
    }
    clean();
}

static void clean()
{
    window_destroy();
    delete camera_o;
    delete camera_p;
    cleanup_gamestates();
    quad_destroy();
    naked_model_destroy();
    resources_destroy();
}

uint32_t get_game_ticks()
{
    return SDL_GetTicks();
}