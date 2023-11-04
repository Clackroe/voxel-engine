#include "Screen.h"
#include <iostream>

int Screen::SCR_WIDTH;
int Screen::SCR_HEIGHT;


Screen::Screen(int SCR_WIDTH, int SCR_HEIGHT, const char* title)
{
    Screen::SCR_WIDTH = SCR_WIDTH;
    Screen::SCR_HEIGHT = SCR_HEIGHT;
    window_title = title;

    glfwInit();

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, window_title, NULL, NULL);
    if (this->window == NULL) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
    }

    initOpenGL();
}

Screen::~Screen()
{
    glfwDestroyWindow(window);
    //TODO: Destroy any additionaly added things (Shaders, textures, etc)
}

int Screen::getWidth()
{
    if (Screen::SCR_WIDTH) {
        return SCR_WIDTH;
    }
    else {
        return -1;
    }
}

int Screen::getHeight()
{
    if (Screen::SCR_HEIGHT) {
        return SCR_HEIGHT;
    }
    else {
        return -1;
    }
}

void Screen::Update()
{
    glfwPollEvents();
    glfwSwapBuffers(this->window);
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        // std::cerr << err << std::endl;
    }
}

void Screen::processInput()
{
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, true);
    }
}

void Screen::Clear()
{
    processInput();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Screen::initOpenGL()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
    }


}


