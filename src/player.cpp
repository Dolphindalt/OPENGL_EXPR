#include <player.h>

#include <event.h>

#define PLAYER_VELOCITY (0.112f);

Player::Player(Character character) : Entity2D()
{
    set_position(glm::vec3(0.0f, 0.0f, 50.0f));
    load_character(character);
    set_scale(0.1);
    hitbox.set_texture(get_texture("assets/textures/player/playerhitbox.png"));
    hitbox.set_scale(0.03);
    hitbox.set_position(0.0f, 0.0f, 40.0f);
}

void Player::update()
{
    Entity::update();
    handle_input();
    hitbox.update();
}

void Player::load_character(Character &character)
{
    switch(character)
    {
        case DOLPHIN:
            set_texture(get_texture("assets/textures/player/dolphin.png"));
            break;
        default:
            break;
    }
}

void Player::render(GLuint model_loc)
{
    shader_load_mat4(model_loc, hitbox.get_model());
    hitbox.render();
    shader_load_mat4(model_loc, get_model());
    Entity2D::render();
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
    hitbox.set_velocity(velocity);
}