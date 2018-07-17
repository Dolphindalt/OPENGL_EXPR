#ifndef MENU_H
#define MENU_H

#include <shaders.h>
#include <Entity.h>

typedef enum current_state { MAIN, DIFFICULTY_SELECT, CHARACTER_SELECT} CurrentState;

typedef enum main_menu_options { PLAY, PRACTICE, REPLAY, SETTINGS, QUIT } MainMenuOptions;

GLuint shader_program;
CurrentState current;
Entity2D background;

void menu_init(GLuint shader_program2d_id);

void menu_enter_loop();

void toggle_main_menu();
void draw_main_menu(GLuint model_location);
void tick_main_menu();


#endif