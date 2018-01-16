#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <SDL2/SDL.h>

#define MAJOR_VERSION 3
#define MINOR_VERSION 1

typedef struct windowdata {
    SDL_Window *window;
    int w, h;

    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);
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