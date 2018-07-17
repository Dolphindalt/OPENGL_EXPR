#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <GL/glew.h>
#include <camera.h>
#include <vector>
#include <Entity.h>

class Renderer2d
{
public:
    Renderer2d(std::vector<Entity2D *> *entities, Camera &camera);
    ~Renderer2d();

    void render();
private:
    GLuint _shader_program;
    Camera _camera;
    std::vector<Entity2D *> *_entities;
};

#endif