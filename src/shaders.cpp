#include <shaders.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <resources.h>
#include <glm/gtc/type_ptr.hpp>

static void shader_compile(const char *src, GLuint &id);

GLuint shader_init(std::string &vertex_path, std::string &fragment_path)
{
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    std::string vertex_code, fragment_code;

    if(!read_file_to_buffer(vertex_path, vertex_code))
    {
        printf("Failed to read shader file: %s at %s : %d\n", vertex_path.c_str(), __FILE__, __LINE__);
        exit(1);
    }
    if(!read_file_to_buffer(fragment_path, fragment_code))
    {
        printf("Failed to read shader file: %s at %s : %d\n", fragment_path.c_str(), __FILE__, __LINE__);
        exit(1);
    }

    shader_compile(vertex_code.c_str(), vertex_shader_id);
    shader_compile(fragment_code.c_str(), fragment_shader_id);

    GLuint shader_program_id = glCreateProgram();
    glAttachShader(shader_program_id, vertex_shader_id);
    glAttachShader(shader_program_id, fragment_shader_id);
    glLinkProgram(shader_program_id);

    GLint result = GL_FALSE;
    int error_length;
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(shader_program_id, GL_INFO_LOG_LENGTH, &error_length);
    if(error_length > 0 && result == GL_FALSE)
    {
        char msg[error_length + 1];
        glGetProgramInfoLog(shader_program_id, error_length, NULL, &msg[0]);
        printf("%s\n", msg);
        exit(1);
    }

    glDetachShader(shader_program_id, vertex_shader_id);
    glDetachShader(shader_program_id, fragment_shader_id);
    glDeleteShader(fragment_shader_id);
    glDeleteShader(vertex_shader_id);

    assert(shader_program_id > 0);

    return shader_program_id;
}

void shader_start(GLuint id)
{
    glUseProgram(id);
}

void shader_stop()
{
    glUseProgram(0);
}

GLuint shader_get_uniform_location(GLuint id, const char *name)
{
    return glGetUniformLocation(id, name);
}

void shader_bind_attribute(GLuint id, GLuint attrib_location, const char *name)
{
    glBindAttribLocation(id, attrib_location, name);
}

void shader_destroy(GLuint id)
{
    glDeleteProgram(id);
}

static void shader_compile(const char *src, GLuint &id)
{
    GLint result = GL_FALSE;
    int error_length;
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &error_length);
    if(error_length > 0 && result == GL_FALSE)
    {
        char msg[error_length + 1];
        glGetShaderInfoLog(id, error_length, NULL, &msg[0]);
        printf("%s\n", msg);
        exit(1);
    }
}

void shader_load_mat4(GLuint location, const glm::mat4 mat)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void shader_load_vec3(GLuint location, const glm::vec3 vec)
{
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void shader_load_float(GLuint location, const float val)
{
    glUniform1f(location, val);
}