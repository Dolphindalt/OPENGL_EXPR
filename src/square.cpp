#include <square.h>

Quad quad;

void quad_init()
{
    float vertices[] = 
    {
        -0.5, -0.5, 0.0,
        -0.5, 0.5, 0.0,
        0.5, 0.5, 0.0,
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.5, 0.5, 0.0
    };

    quad.vertex_count = 6;
    glGenVertexArrays(1, &quad.vao_id);
    glBindVertexArray(quad.vao_id);

    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void quad_render()
{
    glBindVertexArray(quad.vao_id);
    glDrawArrays(GL_TRIANGLES, 0, quad.vertex_count);
    glBindVertexArray(0);
}

void quad_destroy()
{
    glDeleteVertexArrays(1, &(quad.vao_id));
}