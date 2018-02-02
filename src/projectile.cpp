#include <projectile.h>

#include <main.h>

Projectile::Projectile()
{
    birth_time = get_game_ticks();
}

void Projectile::render()
{
    projectile_draw_rule(this, get_game_ticks() - birth_time);
}