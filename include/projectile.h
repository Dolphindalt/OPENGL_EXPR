#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Entity.h>

class Projectile;

typedef int (*ProjectileRule)(Projectile *p, int t);
typedef void (*ProjectileDrawRule)(Projectile *p, int t);

class Projectile : public Entity2D
{
public:
    Projectile();
    void render();
private:
    ProjectileRule projectile_rule;
    ProjectileDrawRule projectile_draw_rule;

    int birth_time;
    bool grazed;
};

#endif