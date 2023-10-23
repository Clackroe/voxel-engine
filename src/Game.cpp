#include "Game.h"
#include <iostream>

Game::Game(int SCR_WIDTH, int SCR_HEIGHT, const char* title)
    : screen(SCR_WIDTH, SCR_HEIGHT, title)
{
    world = new World();
}

Game::~Game()
{
}

bool Game::isRunning() {
    return !glfwWindowShouldClose(screen.window);
}

void Game::update()
{
    world->update();
}


void Game::render() {
    screen.Clear();
    world->render();
    screen.Update();
}
