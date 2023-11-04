#include "world.h"
#include "../Graphics/Texture/Texture.h"

World::World(Player* plyr)
{
    player = plyr;
    glm::vec3 one = { 0.0f, 0.0f, 0.0f };

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    printf("Generate\n");
    Texture::GENERATE_DATA();
    printf("Load\n");
    Texture::LOAD_DATA();
    printf("Done\n");
    Block::loadBlockInfo();


    int w = 8;
    for (int i = 0; i < w;i++) {
        for (int j = 0; j < w; j++) {
            chunk.push_back(new Chunk(glm::vec2(i, j)));

        }
    }

}

World::~World() {
    for (auto c : chunk)
    {
        delete c;
    }
    chunk.clear();

}


void World::render() {


    for (Chunk* c : chunk)
    {
        c->render();

    }

}

void World::update() {

    Renderer::BLOCK->setMat4("view", player->cam->getViewMatrix());
    player->processInput();


}