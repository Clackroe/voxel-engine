#include "Game.h"
#include <iostream>

Input* inpRef;
void mouse_update(GLFWwindow* window, double xPosIn, double yPosIn);

Game::Game(int SCR_WIDTH, int SCR_HEIGHT, const char* title)
    : screen(SCR_WIDTH, SCR_HEIGHT, title), input(&screen), player(&screen, &input)
{
    deltaTime = 0.0f;
    lastFrame = 0.0f;
    inpRef = &input;

    world = new World(&player);

    glfwSetCursorPosCallback(screen.window, mouse_update);

}

Game::~Game()
{
}

bool Game::isRunning() {
    return !glfwWindowShouldClose(screen.window);
}

void Game::update()
{
    screen.Update();

}
void Game::render() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    world->update(deltaTime);
    screen.Clear();
    world->render(deltaTime);
}

void mouse_update(GLFWwindow* window, double xPosIn, double yPosIn) {
    inpRef->setCurrentMousePos(xPosIn, yPosIn);
}