#include "World/world.h"
#include "Graphics/Texture/Texture.h"

World::World(Player* plyr)
{
    player = plyr;
    glm::vec3 one = { 0.0f, 0.0f, 0.0f };

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    printf("Generate\n");
    Texture::GENERATE_DATA();
    printf("Load\n");
    Texture::LOAD_DATA();
    printf("Done\n");
    Block::loadBlockInfo();

    printf("Generating World...\n");
    int w = 4;
    for (int i = -(w / 2); i < w / 2;i++) {
        for (int j = -(w / 2); j < w / 2; j++) {
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


void World::update() {

    Renderer::BLOCK->setMat4("view", player->cam->getViewMatrix());
    player->processInput();


}

void World::render() {


    for (Chunk* c : chunk)
    {
        c->render();

    }

}

