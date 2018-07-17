#ifndef RENDERER3D_H
#define RENDERER3D_H

#include <GL/glew.h>
#include <Entity.h>
#include <camera.h>
#include <vector>

class Renderer3d
{
public:
    Renderer3d(std::vector<Entity3D *> *entities, Camera &camera);
    ~Renderer3d();

    void render();
private:
    GLuint _shader_program;
    Camera _camera;
    std::vector<Entity3D *> *_entities;
};

#endif