#ifndef RENDERER3D_H
#define RENDERER3D_H

#include <GL/glew.h>
#include <Entity.h>
#include <camera.h>
#include <vector>

class Renderer3d
{
public:
    Renderer3d(GLuint shader_program, Camera &camera);
    ~Renderer3d();

    void render();
    void add_entity(Entity3D *entity);
private:
    GLuint _shader_program;
    Camera _camera;
    std::vector<Entity3D *> _entities;
};

#endif