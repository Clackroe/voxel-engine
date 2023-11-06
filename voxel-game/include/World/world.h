#pragma once
#include "Core/core.h"
#include"Graphics/Shader.h"
#include "Player/camera.h"
#include "Player/player.h"
#include "Graphics/VertexArray.h"
// #include "Block.h"
#include "Graphics/Render/Render.h"
#include "World/chunk.h"
class World {

public:
    World(Player* plyr);
    ~World();

    // Block* blocks[2];
    // Block* block;

    Player* player;
    void render();
    void update();

    std::vector<Chunk*> chunk;

public:






};