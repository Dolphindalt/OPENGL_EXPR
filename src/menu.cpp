#include <menu.h>

#include <resources.h>

CurrentState current;
Entity2D background;

extern GLuint _shader_program_2d;

void (*menu_update_function)(double delta);
void (*menu_render_function)(void);

static void draw_main_menu();
static void tick_main_menu(double delta);

void toggle_main_menu()
{
    current = MAIN;
    background.set_texture(get_texture("assets/textures/menu/mainmenu.png"));
    menu_render_function = draw_main_menu;
    menu_update_function = tick_main_menu;
}

void draw_main_menu()
{
    glUseProgram(_shader_program_2d);
    
    background.render();

    glUseProgram(0);
}

void tick_main_menu(double delta)
{

}