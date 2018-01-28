#include <collision.h>

#include <mymath.h>

#include <cmath>
#include <cstdlib>

bool circle_circle_collision(Circle &c1, Circle &c2)
{
    float d = distance(c1.cx, c2.cx, c1.cy, c2.cy); 
    return (d <= c1.radius + c2.radius);
}

bool circle_rectangle_collision(Circle &c, Rectangle &r)
{
    float cdx = abs(c.cx - r.x);
    float cdy = abs(c.cy - r.y);
    if(cdx > (r.w/2 + c.radius)) return false;
    if(cdy > (r.h/2 + c.radius)) return false;
    if(cdx <= (r.w/2)) return true;
    if(cdy <= (r.h/2)) return true;
    float cd_sq = pow(cdx - r.w/2, 2) + pow(cdy - r.h/2, 2);
    return (cd_sq <= (pow(c.radius, 2)));
}

bool rectangle_rectangle_collision(Rectangle &r1, Rectangle &r2)
{
    return (r1.x < r2.x + r2.w && r1.x + r1.w > r2.x
            && r1.y < r2.y + r2.h && r1.y + r1.h > r2.y);
}