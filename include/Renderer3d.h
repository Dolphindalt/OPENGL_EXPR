#ifndef RENDERER3D_H
#define RENDERER3D_H

#include <GL/glew.h>
#include <Entity.h>
#include <camera.h>
#include <vector>

class Renderer3d
{
public:
    Renderer3d();
    ~Renderer3d();

    void render(std::vector<Entity3D *> *entities);
};

#endif