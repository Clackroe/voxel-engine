#pragma once
#include <iostream>
#include "input.h"
#include "camera.h"
#include <set>
#include "../Graphics/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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