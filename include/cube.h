#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>

typedef struct cube {
    GLuint vao_id;
    unsigned int vertex_count;
} Cube;

extern Cube cube;

void cube_init();

void cube_render();

void cube_destroy();

#endif