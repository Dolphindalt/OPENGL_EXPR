#include <player.h>

#include <event.h>

#define PLAYER_VELOCITY (0.02f);

Player::Player() : Entity2D()
{
    set_position(glm::vec3(0.0f, 0.0f, 1.0f));
}

void Player::handle_input()
{
    glm::vec3 velocity = glm::vec3(0.0f);
    if(key_up)
    {
        velocity.y += PLAYER_VELOCITY;
    }
    if(key_down)
    {
        velocity.y -= PLAYER_VELOCITY;
    }
    if(key_left)
    {
        velocity.x -= PLAYER_VELOCITY;
    }
    if(key_right)
    {
        velocity.x += PLAYER_VELOCITY;
    }
    set_velocity(velocity);
}

void Player::switch_to_character(Character &character)
{

}