#pragma once
#include "Graphics/Screen.h"
#include "World/world.h"

class Game {


public:
    Game(int SCR_WIDTH, int SCR_HEIGHT, const char* title);
    ~Game();
    // bool isRunning = false;
    bool isRunning();
    void update();
    void render();

private:
    Screen screen;
    World* world;
};
