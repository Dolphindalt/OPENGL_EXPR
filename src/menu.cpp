#include <menu.h>

#include <resources.h>

void menu_init(GLuint shader_program2d_id)
{
    shader_program = shader_program2d_id;
}

void menu_enter_loop()
{
    current = MAIN;
    for(;;)
    {
        switch(current)
        {
            case MAIN:
                draw_main_menu();
                tick_main_menu();
                break;
            default:
                break;
        }
    }
}

void toggle_main_menu()
{
    current = MAIN;
    background.set_texture(get_texture("assets/textures/menu/mainmenu.png"));
}

void draw_main_menu()
{
    glUseProgram(shader_program);
    
    background.render();

    glUseProgram(0);
}

void tick_main_menu()
{

}