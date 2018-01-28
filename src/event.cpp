#include <event.h>

#include <SDL2/SDL.h>
#include <cstdio>

bool key_up, key_down, key_left, key_right;

void handle_input(bool &running)
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT: running = false; break;
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym)
                {
                    case SDLK_LEFT: key_left = true; break;
                    case SDLK_RIGHT: key_right = true; break;
                    case SDLK_UP: key_up = true; break;
                    case SDLK_DOWN: key_down = true; break;
                }
                break;
            case SDL_KEYUP:
                switch(e.key.keysym.sym)
                {
                    case SDLK_LEFT: key_left = false; break;
                    case SDLK_RIGHT: key_right = false; break;
                    case SDLK_UP: key_up = false; break;
                    case SDLK_DOWN: key_down = false; break;
                }
                break;
            default: break;
        }
    }
}

