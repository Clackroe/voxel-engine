#pragma once
#include <iostream>
#include "input.h"
#include "camera.h"
#include <set>

class Player {
public:

    Player(Screen* scr, Input* inp);
    void update();
    void render();
    void processInput(float deltaTime);

    Camera* cam;
private:
    void processMouseLook();
    void processKeyboard(float deltaTime);

    Screen* screen;
    Input* input;



};