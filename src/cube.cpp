#include <cube.h>

Cube cube;

void cube_init()
{
    float vertices[] =
    {
        -.0f,-.0f,-.0f, // triangle 1 : begin
        -.0f,-.0f, .0f,
        -.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-.0f, // triangle 2 : begin
        -.0f,-.0f,-.0f,
        -.0f, 1.0f,-.0f, // triangle 2 : end
        1.0f,-.0f, 1.0f,
        -.0f,-.0f,-.0f,
        1.0f,-.0f,-.0f,
        1.0f, 1.0f,-.0f,
        1.0f,-.0f,-.0f,
        -.0f,-.0f,-.0f,
        -.0f,-.0f,-.0f,
        -.0f, 1.0f, 1.0f,
        -.0f, 1.0f,-.0f,
        1.0f,-.0f, 1.0f,
        -.0f,-.0f, 1.0f,
        -.0f,-.0f,-.0f,
        -.0f, 1.0f, 1.0f,
        -.0f,-.0f, 1.0f,
        1.0f,-.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-.0f,-.0f,
        1.0f, 1.0f,-.0f,
        1.0f,-.0f,-.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-.0f,
        -.0f, 1.0f,-.0f,
        1.0f, 1.0f, 1.0f,
        -.0f, 1.0f,-.0f,
        -.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -.0f, 1.0f, 1.0f,
        1.0f,-.0f, 1.0f
    };

    cube.vertex_count = 36;
    glGenVertexArrays(1, &cube.vao_id);
    glBindVertexArray(cube.vao_id);

    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void cube_render()
{
    glBindVertexArray(cube.vao_id);
    glDrawArrays(GL_TRIANGLES, 0, cube.vertex_count);
    glBindVertexArray(0);
}

void cube_destroy()
{
    glDeleteVertexArrays(1, &(cube.vao_id));
}