#include <player.h>

#include <event.h>

#define PLAYER_VELOCITY (0.1f)

Player::Player(Character character) : Entity2D()
{
    set_position(glm::vec3(0.0f, 0.0f, 49.0f));
    load_character(character);
    set_scale(0.1);
    hitbox.set_texture(get_texture("assets/textures/player/playerhitbox.png"));
    hitbox.set_scale(0.1);
    hitbox.set_position(0.0f, 0.0f, 50.0f);
}

void Player::update(double delta)
{
    Entity::update(delta);
    handle_input(delta);
    hitbox.update(delta);
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
    shader_load_mat4(model_loc, get_model());
    Entity2D::render();
    if(hitbox_visible)
    {
        shader_load_mat4(model_loc, hitbox.get_model());
        hitbox.render();
    }
}

void Player::handle_input(double delta)
{
    glm::vec3 velocity = glm::vec3(0.0f);
    double dx = PLAYER_VELOCITY * delta;
    if(key_up)
    {
        velocity.y += dx;
    }
    if(key_down)
    {
        velocity.y -= dx;
    }
    if(key_left)
    {
        velocity.x -= dx;
    }
    if(key_right)
    {
        velocity.x += dx;
    }
    
    hitbox_visible = key_lshift;

    set_velocity(velocity);
    hitbox.set_velocity(velocity);
}