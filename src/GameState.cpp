#include <GameState.h>

#include <cassert>
#include <player.h>
#include <menu.h>
#include <objloader.h>
#include <resources.h>

Player *player;

GameState *currentState;
#define GAMESTATES_LENGTH 2
GameState **gamestates;

Renderer2d *renderer2d;
Renderer3d *renderer3d;

void init_gamestates()
{
    gamestates = new GameState *[2];
    gamestates[0] = new MenuState();
    gamestates[1] = new PlayState();

    renderer2d = new Renderer2d();
    renderer3d = new Renderer3d();
}

void switchToState(int state)
{
    assert(state < GAMESTATES_LENGTH);
    currentState = gamestates[state];
}

void cleanup_gamestates()
{
    delete gamestates[0];
    delete gamestates[1];
}

GameState::~GameState()
{

}

MenuState::MenuState()
{
    init_menus();
    toggle_main_menu();
}

MenuState::~MenuState()
{
    destroy_menus();
}

void MenuState::update(double delta)
{
    (*menu_update_function)(delta);
}

void MenuState::render()
{
    renderer2d->render(getMenuEntities());
}

PlayState::PlayState()
{
    player = new Player(DOLPHIN);
    _es = new EntityService(renderer2d, renderer3d);

    TexturedModel tm = load_textured_model("assets/fish.obj", "assets/textures/fish.png");
    Entity3D *dragon = new Entity3D(tm);
    dragon->set_velocity(0.0f, 0.0f, 0.0f);
    dragon->set_scale(0.1f);

    _es->addEntity(dragon);

    Entity2D *grass = new Entity2D("assets/textures/grass.png");
    grass->set_position(-1.0f, -1.0f, 0.0f);
    grass->set_scale(0.5f);
    Entity2D *grass2 = new Entity2D("assets/textures/grass.png");
    grass2->set_position(1.0f, -1.0f, 0.0);
    grass2->set_scale(0.5f);

    _es->addEntity(grass);
    _es->addEntity(grass2);
}

PlayState::~PlayState()
{
    delete player;
    delete _es;
}

void PlayState::update(double delta)
{
    _es->updateFlatEntities(delta);
    _es->updateThiccEntities(delta);
}

void PlayState::render()
{
    _es->render();
}