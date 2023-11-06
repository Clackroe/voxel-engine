#pragma once
#include <utility>
#include "../Core/core.h"
#include "../Graphics/Screen.h"
#include <set>
#include <map>
#include <glm/glm.hpp>



namespace Input {


    extern double xPos, yPos;
    inline bool firstMouse;
    inline float lastX;
    inline float lastY;

    inline bool keyPressed[GLFW_KEY_LAST] = {};
    inline bool keyBeginPressData[GLFW_KEY_LAST] = {};
    inline bool mousePressed[GLFW_MOUSE_BUTTON_LAST] = {};
    inline bool mouseBeginPressData[GLFW_MOUSE_BUTTON_LAST] = {};

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouseCallback(GLFWwindow* window, double xPos, double yPos);
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    bool isKeyPressed(int key);
    bool keyBeginPress(int key);
    bool isMousePressed(int button);
    bool mouseBeginPress(int button);
};