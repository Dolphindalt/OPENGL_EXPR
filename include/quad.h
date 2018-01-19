#ifndef QUAD_H
#define QUAD_H

#include <GL/glew.h>

typedef struct quad {
    GLuint vao_id;
    unsigned int vertex_count;
} Quad;

void quad_init();

void quad_render();

void quad_destroy();

#endif