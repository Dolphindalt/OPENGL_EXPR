#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>

typedef enum character { DOLPHIN } Character;

class Player : public Entity2D
{
public:
    Player(Character character);
    void update(double delta);
    void load_character(Character &character);
    void render(GLuint model_loc);
private:
    void handle_input(double delta);

    Entity2D hitbox;
    bool hitbox_visible;
};

#endif