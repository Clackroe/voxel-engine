#include "Player/input.h"




double Input::xPos, Input::yPos;

namespace Input {


    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {

        if (key < 0 || key > GLFW_KEY_LAST)
        {
            return;
        }

        if (action == GLFW_PRESS)
        {
            keyPressed[key] = true;
            keyBeginPressData[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keyPressed[key] = false;
            keyBeginPressData[key] = false;
        }
    }

    void mouseCallback(GLFWwindow* window, double xPos, double yPos)
    {
        //printf("X, y: <%f, %f>", xPos, yPos);
        Input::xPos = xPos;
        Input::yPos = yPos;

    }
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {

        if (action == GLFW_PRESS)
        {
            mousePressed[button] = true;
            mouseBeginPressData[button] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            mousePressed[button] = false;
            mouseBeginPressData[button] = false;
        }

    }

    bool isKeyPressed(int key)
    {
        return keyPressed[key];
    }

    bool keyBeginPress(int key)
    {
        return keyBeginPressData[key];
    }

    bool isMousePressed(int mouseButton)
    {
        return mousePressed[mouseButton];
    }

    bool mouseBeginPress(int mouseButton)
    {
        return mouseBeginPressData[mouseButton];
    }



}