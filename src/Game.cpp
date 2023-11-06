
#include "Game.h"

float Time::deltaTime;
float Time::lastFrame;

Game::Game(int SCR_WIDTH, int SCR_HEIGHT, const char* title)
    : screen(SCR_WIDTH, SCR_HEIGHT, title), player(&screen)
{
    Time::deltaTime = 0.0f;
    Time::lastFrame = 0.0f;

    world = new World(&player);


}

Game::~Game()
{
    delete world;
}

bool Game::isRunning() {
    return !glfwWindowShouldClose(screen.window);
}

void Game::update()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    Time::deltaTime = currentFrame - Time::lastFrame;
    Time::lastFrame = currentFrame;


    screen.Update();
    player.update();
    world->update();

}
void Game::render() {
    screen.Clear();
    world->render();
}
