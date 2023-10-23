#include <iostream>
#include "input.h"


Input::Input(Screen* scr) {
    screen = scr;
    firstMouse = true;

    lastX = scr->getWidth() / 2.0f;
    lastY = scr->getHeight() / 2.0f;

    keyBinds = {
       {GLFW_KEY_W, FORWARD_KEY},
       {GLFW_KEY_S, BACKWARD_KEY},
       {GLFW_KEY_A, LEFT_KEY},
       {GLFW_KEY_D, RIGHT_KEY}
    };



}

void Input::setCurrentMousePos(double xPosIn, double yPosIn) {
    xPos = xPosIn;
    yPos = yPosIn;
    // std::cout << xPos << std::endl;
}

std::pair<float, float> Input::getMouseOffets() {

    float xpos = static_cast<float>(xPos);
    float ypos = static_cast<float>(yPos);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    return std::make_pair(xoffset, yoffset);
}

std::set<int> Input::getKey() {
    std::set<int> out;
    for (const auto& myPair : keyBinds) {
        if (glfwGetKey(screen->window, myPair.first) == GLFW_PRESS) {

            out.insert(myPair.second);
        }
    }

    return out;

}