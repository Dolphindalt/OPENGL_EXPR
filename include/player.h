#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>

typedef enum character { PLAYER1, PLAYER2 } Character;

class Player : public Entity2D
{
public:
    Player();
    void handle_input();
    void switch_to_character(Character &character);
private:
    
};

#endif