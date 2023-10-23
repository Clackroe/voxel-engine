#pragma once
#include <utility>
#include "../Graphics/Screen.h"
#include <set>
#include <map>

enum input_keys {
    FORWARD_KEY,
    BACKWARD_KEY,
    LEFT_KEY,
    RIGHT_KEY
};


class Input {


public:

    std::map<int, int> keyBinds;
    Input(Screen* scr);
    Screen* screen;
    bool firstMouse;

    float lastX;
    float lastY;

    void setCurrentMousePos(double xPos, double yPos);


    std::pair<float, float> getMouseOffets();
    std::set<int> getKey();

private:
    double xPos, yPos;

    // void mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn)


};