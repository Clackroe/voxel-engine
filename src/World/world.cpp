#include "world.h"

World::World(Player* plyr)
{
    player = plyr;
    glm::vec3 one = { 0.0f, 0.0f, 0.0f };

    // block = new Block(0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    chunk = new Chunk(glm::vec2(0.0, 0.0));
}

World::~World() {

}


void World::render(float deltaTime) {

    chunk->render();





    // block->render(player->cam->getViewMatrix());
    // Block* block2 = new Block({ 0.0, 1.0, 0.0 });
    // block2->render(player->cam->getViewMatrix());



    // Renderer::renderBlock({ 0.0f, 0.0f, 0.0f });
    // Renderer::renderBlock({ 1.0f, 0.0f, 0.0f });
    // Renderer::renderBlock({ 0.0f, 1.0f, 0.0f });
    // blocks[0]->render();
    // vao->render();
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void World::update(float deltaTime) {


    Renderer::BLOCK->setMat4("view", player->cam->getViewMatrix());
    player->processInput(deltaTime);


}