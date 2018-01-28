#include <quad.h>

Quad quad;

void quad_init()
{

    /*float vertices[] =
    {
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        1.0, 1.0, 0.0
    };*/

    float vertices[] =
    {
        -1.0, 1.0, 0.0,
        -1.0, -1.0, 0.0,
        1.0, -1.0, 0.0,
        -1.0, 1.0, 0.0,
        1.0, -1.0, 0.0,
        1.0, 1.0, 0.0
    };

    float uvs[] =
    {
        0.0, 1.0,
        0.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 0.0,
        1.0, 1.0
    };

    quad.vertex_count = 6;
    glGenVertexArrays(1, &quad.vao_id);
    glBindVertexArray(quad.vao_id);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    GLuint vbo_verts;
    glGenBuffers(1, &vbo_verts);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_verts);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    GLuint vbo_uvs;
    glGenBuffers(1, &vbo_uvs);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    
    glBindVertexArray(0);
}

void quad_render()
{
    glBindVertexArray(quad.vao_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, quad.vertex_count);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void quad_destroy()
{
    glDeleteVertexArrays(1, &(quad.vao_id));
}