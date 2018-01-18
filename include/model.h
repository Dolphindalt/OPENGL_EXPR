#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <vector>

using namespace std;

typedef struct naked_model {
    GLuint vao_id;
    unsigned int indices;
} NakedModel;

static inline void naked_model_draw(NakedModel &model)
{
    glBindVertexArray(model.vao_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDrawArrays(GL_TRIANGLES, 0, model.indices);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

static inline NakedModel load_attribs_to_vao(const std::vector<GLfloat> &vertices, const vector<GLuint> &indices, const vector<GLfloat> &normals, const vector<GLfloat> &texture)
{
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    GLuint element_vbo_buffer;
    glGenBuffers(1, &element_vbo_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    store_data_in_attrib_list(0, 3, vertices);
    store_data_in_attrib_list(1, 2, texture);
    store_data_in_attrib_list(2, 3, normals);
    glBindVertexArray(0);
    return { vao_id, (GLuint)indices.size() };
}

static inline void store_data_in_attrib_list(int id, int size, const vector<float> &data)
{
    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), data.data, GL_STATIC_DRAW);
    glVertexAttribPointer(id, size, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#endif