#pragma once
#include "Graphics/Render/Render.h"
#include "Graphics/Screen.h"
#include "World/world.h"
#include "player/input.h"
#include "player/player.h"
class Game {


public:
    Game(int SCR_WIDTH, int SCR_HEIGHT, const char* title);
    ~Game();

    bool isRunning();
    void update();
    void render();

private:
    Screen screen;
    World* world;
    Player player;
};
