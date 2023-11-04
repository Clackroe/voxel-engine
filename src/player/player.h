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


    Player(Screen* scr);
    ~Player();
    void update();
    void render();
    void processInput();

    Camera* cam;
private:
    void processMouseLook();
    void processKeyboard();
    Renderer* rnd;

    Screen* screen;




};