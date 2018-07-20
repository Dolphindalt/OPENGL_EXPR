#include <main.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <window.h>
#include <event.h>
#include <shaders.h>
#include <quad.h>
#include <camera.h>
#include <model.h>
#include <objloader.h>
#include <resources.h>
#include <Entity.h>
#include <glm/gtx/transform.hpp>
#include <EntityService.h>
#include <player.h>

#include <cassert>

static void init();
static bool gl_init();
static void game_loop();
static void input();
static void render();
static void clean();

#define TICK_INTERVAL 60.0

bool running = true;
Camera camera_p, camera_o;
EntityService *es;
Player *player;

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

    player = new Player(DOLPHIN);

    es = new EntityService();

    TexturedModel tm = load_textured_model("assets/fish.obj", "assets/textures/fish.png");
    Entity3D *dragon = new Entity3D(tm);
    dragon->set_velocity(0.0f, 0.0f, 0.0f);
    dragon->set_scale(0.1f);

    es->addEntity(dragon);

    Entity2D *grass = new Entity2D("assets/textures/grass.png");
    grass->set_position(-1.0f, -1.0f, 0.0f);
    grass->set_scale(0.5f);
    Entity2D *grass2 = new Entity2D("assets/textures/grass.png");
    grass2->set_position(1.0f, -1.0f, 0.0);
    grass2->set_scale(0.5f);

    es->addEntity(grass);
    es->addEntity(grass2);

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
            input();
            es->updateFlatEntities(delta);
            es->updateThiccEntities(delta);
            delta--;
        }

        render();

        frames++;
        if(SDL_GetTicks() - timer > 1000)
        {
            timer += 1000;
            frames = 0;
        }
    }
    clean();
}

static void input()
{
    handle_input(running);
}

static void render()
{
    window.clear();
    es->render();
    window.swap_buffer();
}

static void clean()
{
    delete es;
    window_destroy();
    quad_destroy();
    naked_model_destroy();
    resources_destroy();
}

uint32_t get_game_ticks()
{
    return SDL_GetTicks();
}