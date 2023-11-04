#pragma once
#include <iostream>
#include "../Core/core.h"
#include "input.h"
#include "camera.h"
#include <set>
#include "../Graphics/Shader.h"
#include "../Graphics/Render/Render.h"
#include "../World/Block.h"

class Player {
public:


    Player(Screen* scr, Input* inp);
    ~Player();
    void update();
    void render();
    void processInput(float deltaTime);

    Camera* cam;
private:
    void processMouseLook();
    void processKeyboard(float deltaTime);
    Renderer* rnd;

    Screen* screen;
    Input* input;



};