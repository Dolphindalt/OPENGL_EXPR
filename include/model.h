#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <vector>
#include <map>
#include <resources.h>

using namespace std;

static vector<GLuint> vaos, vbos;

typedef struct naked_model {
    GLuint vao_id;
    size_t indices;
} NakedModel;

typedef struct textured_model {
    NakedModel model;
    Texture *texture;
} TexturedModel;

static inline void store_data_in_attrib_list(int id, int size, void *data, int data_size)
{
    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(id);
    glVertexAttribPointer(id, size, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vbos.push_back(vbo_id);
}

static inline void textured_model_render(TexturedModel &model)
{
    glBindVertexArray(model.model.vao_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.texture->texture_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDrawElements(GL_TRIANGLES, model.model.indices, GL_UNSIGNED_SHORT, (void *)0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

static inline void naked_model_render(NakedModel &model)
{
    glBindVertexArray(model.vao_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDrawElements(GL_TRIANGLES, model.indices, GL_UNSIGNED_SHORT, (void *)0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

static inline void naked_model_destroy()
{
    for(auto i : vaos)
        glDeleteVertexArrays(1, &i);
    for(auto& i : vbos)
        glDeleteBuffers(1, &i);
}

static inline NakedModel load_attribs_to_vao(vector<glm::vec3> &vertices, vector<glm::vec2> &texture, vector<glm::vec3> &normals, vector<unsigned short> &indices)
{
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    GLuint element_vbo_buffer;
    glGenBuffers(1, &element_vbo_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);

    store_data_in_attrib_list(0, 3, &vertices[0], vertices.size() * sizeof(glm::vec3));
    store_data_in_attrib_list(1, 2, &texture[0], texture.size() * sizeof(glm::vec2));
    store_data_in_attrib_list(2, 3, &normals[0], normals.size() * sizeof(glm::vec3));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
    vaos.push_back(vao_id);
    vbos.push_back(element_vbo_buffer);
    return { vao_id, indices.size() };
}

#endif