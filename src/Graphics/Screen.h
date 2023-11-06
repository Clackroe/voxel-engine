#pragma once
#include "../Core/core.h"
#include "../player/input.h"

class Screen {
public:

    // Screen();
    Screen(int SCR_WIDTH, int SCR_HEIGHT, const char* title);
    ~Screen();

    static int getWidth();
    static int getHeight();
    void Update();
    void Clear();


    GLFWwindow* window;

private:
    static int SCR_WIDTH, SCR_HEIGHT;
    const char* window_title;
    void initOpenGL();
    void processInput();
    void initCallbacks();

};