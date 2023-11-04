#include "player.h"


Player::Player(Screen* scr, Input* inp) {
    screen = scr;
    input = inp;
    cam = new Camera(0.0f, 200.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    rnd = new Renderer(cam);


}
Player::~Player() {
    std::cout << "del cam" << std::endl;
    delete cam;
    delete rnd;
}

void Player::update() {
    // std::cout << fixed;
    // std::cout.precision(2);
    // std::cout << "X: " << cam->cameraPosition.x << " Y: " << cam->cameraPosition.y << " Z: " << cam->cameraPosition.z << std::endl;
}

void Player::render() {
}


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