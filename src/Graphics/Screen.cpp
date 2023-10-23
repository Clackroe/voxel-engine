#include "Screen.h"
#include <iostream>


Screen::Screen(int SCR_WIDTH, int SCR_HEIGHT, const char* title)
{
    this->SCR_WIDTH = SCR_WIDTH;
    this->SCR_HEIGHT = SCR_HEIGHT;
    this->window_title = title;

    glfwInit();

    this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, window_title, NULL, NULL);
    if (this->window == NULL) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
    }

    initOpenGL();
}

Screen::~Screen()
{
    glfwDestroyWindow(this->window);
    //TODO: Destroy any additionaly added things (Shaders, textures, etc)
}

int Screen::getWidth()
{
    return SCR_WIDTH;
}

int Screen::getHeight()
{
    return SCR_HEIGHT;
}

void Screen::Update()
{
    glfwSwapBuffers(this->window);
    glfwPollEvents();
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

    glfwMakeContextCurrent(this->window);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
    }


}


