#pragma once
#include <vector>
#include "../Core/core.h"
#include "../Graphics/Render/Render.h"
#include "Block.h"
#include "../vendor/stb_image.h"



class Chunk {


    struct BlockData {
        Block::BlockType ID;
        //BlockData* someDataObj
    };

    VertexArray* vao;

    int canRender(int x, int y, int z);

    // void addFace(GLfloat* vertices, GLuint* indices, GLfloat* texCoords, GLint* vcount, GLint* icount, int* baseVertex, int* baseIndex, int* baseTex, int* fCursor, int* x, int* y, int* z, Block::FaceIndex f);
    GLfloat* vertices;
    GLuint* indices;
    GLfloat* texCoords;




public:

    Chunk(glm::vec2 position);
    ~Chunk();

    void test();

    const int CHUNK_SIZE_X = 16;  // X dimension size of a chunk
    const int CHUNK_SIZE_Y = 256; // Y dimension size of a chunk
    const int CHUNK_SIZE_Z = 16;  // Z dimension size of a chunk



    std::vector<std::vector<std::vector<BlockData>>> blocks;
    // Block* blocks;

    void createMesh();
    void render();

    glm::vec2 pos;


};