#include "player.h"


Player::Player(Screen* scr) {
    screen = scr;
    // input = inp;
    cam = new Camera(0.0f, 200.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    rnd = new Renderer();


}
Player::~Player() {
    delete cam;
    delete rnd;
}

void Player::update() {
    processInput();
}

void Player::render() {
}


void Player::processInput() {

    processMouseLook();
    processKeyboard();
}

void Player::processMouseLook() {

    cam->processMouseInput();
}

void Player::processKeyboard() {

    if (Input::isKeyPressed(GLFW_KEY_W)) {
        cam->processKeyboardInput(FORWARD);
    }
    if (Input::isKeyPressed(GLFW_KEY_S)) {
        cam->processKeyboardInput(BACKWARD);
    }
    if (Input::isKeyPressed(GLFW_KEY_A)) {
        cam->processKeyboardInput(LEFT);
    }
    if (Input::isKeyPressed(GLFW_KEY_D)) {
        cam->processKeyboardInput(RIGHT);
    }
    if (Input::isKeyPressed(GLFW_KEY_SPACE)) {
        cam->processKeyboardInput(UP);
    }
    if (Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        cam->processKeyboardInput(DOWN);
    }
    else if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(screen->window, true);
    }

}