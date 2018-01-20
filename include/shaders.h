#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

GLuint shader_init(const std::string &vertex_path, const std::string &fragment_path);
void shader_start(GLuint id);
void shader_stop();
GLuint shader_get_uniform_location(GLuint id, const char *name);
void shader_bind_attribute(GLuint id, GLuint attrib_loc, const char *name);
void shader_destroy(GLuint id);

void shader_load_mat4(GLuint location, const glm::mat4 mat);
void shader_load_vec3(GLuint location, const glm::vec3 vec);
void shader_load_float(GLuint location, const float val);

#endif