#ifndef MENU_H
#define MENU_H

#include <shaders.h>
#include <Entity.h>

typedef enum current_state { MAIN, DIFFICULTY_SELECT, CHARACTER_SELECT} CurrentState;

typedef enum main_menu_options { PLAY, PRACTICE, REPLAY, SETTINGS, QUIT } MainMenuOptions;

extern void (*menu_update_function)(double delta);
extern void (*menu_render_function)(void);

void init_menus();
std::vector<Entity2D *> *getMenuEntities();
void toggle_main_menu();
void destroy_menus();

#endif