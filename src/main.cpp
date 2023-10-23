#include "Game.h"

int main() {

    Game game(1920, 1080, "Very Cool Voxel Game");


    while (game.isRunning()) {

        game.render();
    }

    return 0;
}