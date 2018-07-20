#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <EntityService.h>

void init_gamestates();

void switchToState(int state);

void cleanup_gamestates();

class GameState
{
public:
    virtual ~GameState();

    virtual void update(double delta) = 0;
    virtual void render() = 0;
};

class MenuState : public GameState
{
public:
    MenuState();
    ~MenuState();

    void update(double delta);
    void render();
};

class PlayState : public GameState
{
public:
    PlayState();
    ~PlayState();

    void update(double delta);
    void render();
private:
    EntityService *_es;
};

#endif