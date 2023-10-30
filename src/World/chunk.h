#pragma once
#include <vector>
#include "../Core/core.h"
#include "../Graphics/Render/Render.h"
#include "Block.h"
#include "../vendor/stb_image.h"



class Chunk {

    inline static int CHUNK_WIDTH = 16;

    struct Block {
        BlockType ID;
        //BlockData* someDataObj
    };

    VertexArray* vao;




public:

    Chunk(glm::vec2 position);
    ~Chunk();

    void test();

    const int CHUNK_SIZE_X = 16;  // X dimension size of a chunk
    const int CHUNK_SIZE_Y = 256; // Y dimension size of a chunk
    const int CHUNK_SIZE_Z = 16;  // Z dimension size of a chunk



    std::vector<std::vector<std::vector<Block>>> blocks;

    void createMesh();
    void render();

    glm::vec2 pos;


};