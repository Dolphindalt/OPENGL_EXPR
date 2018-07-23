#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <GL/glew.h>
#include <camera.h>
#include <vector>
#include <Entity.h>

class Renderer2d
{
public:
    Renderer2d();
    ~Renderer2d();

    void render(std::vector<Entity2D *> *entities);
};

#endif