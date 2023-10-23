#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Screen {
public:

    // Screen();
    Screen(int SCR_WIDTH, int SCR_HEIGHT, const char* title);
    ~Screen();

    int getWidth();
    int getHeight();
    void Update();
    void Clear();

    GLFWwindow* window;

private:
    int SCR_WIDTH, SCR_HEIGHT;
    const char* window_title;
    void initOpenGL();
    void processInput();

};