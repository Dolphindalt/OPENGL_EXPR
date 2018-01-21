#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <SDL2/SDL.h>

#define MAJOR_VERSION 3
#define MINOR_VERSION 1

typedef struct windowdata {
    SDL_Window *window;
    int w, h;
    float _r = 0.0, _g = 0.0, _b = 0.0, _a = 1.0;

    void set_clear_color(float r, float g, float b, float a)
    {
        _r = r;
        _g = g;
        _b = b;
        _a = a;
    }

    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(_r, _g, _b, _a);
    }

    void swap_buffer()
    {
        SDL_GL_SwapWindow(window);
    }

    double get_aspect_ratio()
    {
        SDL_GL_GetDrawableSize(window, &w, &h);
        return (double) w / (double) h;
    }
} WindowData;

extern WindowData window;

void window_init();

void window_destroy();

#endif