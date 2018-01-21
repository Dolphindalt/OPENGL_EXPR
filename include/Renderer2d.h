#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <GL/glew.h>
#include <camera.h>
#include <vector>

class Renderer2d
{
public:
    Renderer2d(GLuint shader_program, Camera &camera);
    ~Renderer2d();

    void render();
private:
    GLuint _shader_program;
    Camera _camera;
    std::vector<Entity2D *> _entities;
};

#endif