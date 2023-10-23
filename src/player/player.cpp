#include "player.h"


Player::Player(Screen* scr, Input* inp) {
    screen = scr;
    input = inp;
    cam = new Camera();
}

void Player::update() {

}

void Player::render() {}


void Player::processInput(float deltaTime) {

    processKeyboard(deltaTime);
    processMouseLook();
}

void Player::processMouseLook() {


    std::pair<float, float> offsets = input->getMouseOffets();
    cam->processMouseInput(offsets.first, offsets.second);


}

void Player::processKeyboard(float deltaTime) {

    std::set<int> keys = input->getKey();

    // std::cout << keys.count(FORWARD) << std::endl;

    if (keys.find(FORWARD) != keys.end())
        cam->processKeyboardInput(FORWARD, deltaTime);
    if (keys.find(BACKWARD) != keys.end())
        cam->processKeyboardInput(BACKWARD, deltaTime);
    if (keys.find(LEFT) != keys.end())
        cam->processKeyboardInput(LEFT, deltaTime);
    if (keys.find(RIGHT) != keys.end())
        cam->processKeyboardInput(RIGHT, deltaTime);
}