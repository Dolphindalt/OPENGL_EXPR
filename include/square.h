#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>

typedef struct quad {
    GLuint vao_id;
    unsigned int vertex_count;
} Quad;

extern Quad quad;

void quad_init();

void quad_render();

void quad_destroy();

#endif