#include "world.h"

World::World(Player* plyr)
{
    player = plyr;
    glm::vec3 one = { 0.0f, 0.0f, 0.0f };

    block = new Block(0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
}

World::~World() {

}


void World::render(float deltaTime) {


    block->render(player->cam->getViewMatrix());
    Block* block2 = new Block({ 0.0, 1.0, 0.0 });
    block2->render(player->cam->getViewMatrix());

    // blocks[0]->render();
    // vao->render();
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void World::update(float deltaTime) {

    player->processInput(deltaTime);

}