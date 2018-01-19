#include <window.h>

#include <cassert>

WindowData window;

void window_init()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window.window = SDL_CreateWindow("Quad", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_OPENGL);
    assert(window.window != NULL);
    SDL_GLContext glcon = SDL_GL_CreateContext(window.window);
    assert(glcon != NULL);
    GLenum err = glewInit();
    assert(err == GLEW_OK);

    SDL_GL_SetSwapInterval(1); // vsync
}

void window_destroy()
{
    SDL_DestroyWindow(window.window);
}