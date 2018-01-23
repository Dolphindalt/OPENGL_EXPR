#ifndef COLLISION_H
#define COLLISION_H

typedef struct circle {
    float cx, cy, radius;
} Circle;

typedef struct rectangle {
    float x, y, w, h;
} Rectangle;

bool circle_circle_collision(Circle &c1, Circle &c2);

bool circle_rectangle_collision(Circle &c, Rectangle &r);

bool rectangle_rectangle_collision(Rectangle &r1, Rectangle &r2);

#endif