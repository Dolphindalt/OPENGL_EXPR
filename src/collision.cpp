#include <collision.h>

#include <mymath.h>

bool circle_circle_collision(Circle &c1, Circle &c2)
{
    float d = distance(c1.cx, c2.cx, c1.cy, c2.cy); 
    return (d <= c1.radius + c2.radius);
}

bool circle_rectangle_collision(Circle &c, Rectangle &r)
{

}

bool rectangle_rectangle_collision(Rectangle &r1, Rectangle &r2)
{
    
}