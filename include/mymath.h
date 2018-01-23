#ifndef MYMATH_H
#define MYMATH_H

#include <cmath>

#define DISTANCE(type) \
static inline type distance( type ax, type ay, type bx, type by) \
{ \
    return ( type )sqrt(pow(ax - bx, 2) + pow(ay - by, 2)); \
} \

DISTANCE(float)

DISTANCE(double)

DISTANCE(int)

#endif