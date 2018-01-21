#ifndef RESOURCES_H
#define RESOURCES_H

#include <GL/glew.h>
#include <vector>
#include <string>

typedef struct texture {
    GLuint texture_id;
} Texture;

bool read_file_to_buffer(const std::string &path, std::vector<unsigned char> &buffer);
bool read_file_to_buffer(const std::string &path, std::string &buffer);
GLuint load_png(std::string &path);
Texture *get_texture(const std::string &path);
void resources_destroy();

#endif