#include <menu.h>

#include <resources.h>

CurrentState current;
std::vector<Entity2D *> *entities;

extern GLuint _shader_program_2d;

void (*menu_update_function)(double delta);
void (*menu_render_function)(void);

static void tick_main_menu(double delta);

void init_menus()
{
    entities = new std::vector<Entity2D *>();
    Entity2D *background = new Entity2D();
    background->set_position(-1.0f, -1.0f, 0.0f);
    entities->push_back(background);
}

std::vector<Entity2D *> *getMenuEntities()
{
    return entities;
}

void toggle_main_menu()
{
    current = MAIN;
    Texture *texture = get_texture("assets/textures/menu/mainmenu.png");
    entities->at(0)->set_texture(texture);
    menu_update_function = tick_main_menu;
}

void tick_main_menu(double delta)
{

}

void destroy_menus() {
    for(auto i = entities->size(); i-- > 0;)
        delete entities->at(i);
    delete entities;
}