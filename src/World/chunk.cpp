#include "chunk.h"



Chunk::Chunk(glm::vec2 position)
{
    this->pos = position;

    std::cout << "INITIALIZING CHUNK" << std::endl;

    blocks.resize(CHUNK_SIZE_X, std::vector<std::vector<Block>>(CHUNK_SIZE_Y, std::vector<Block>(CHUNK_SIZE_Z, { BlockType::AIR })));

    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int y = 0; y < CHUNK_SIZE_Y; y++) {
            for (int z = 0; z < CHUNK_SIZE_Z; z++) {
                if (z % 2 == 0 && x % 2 == 0) {
                    blocks[x][y][z] = { Block({BlockType::STONE}) };
                }
                else {
                    blocks[x][y][z] = { Block({BlockType::AIR}) };
                }
            }
        }
    }

    std::cout << "FINISHED INITIALIZING CHUNK" << std::endl;

    createMesh();


}

Chunk::~Chunk()
{
    delete vao;
}

void Chunk::createMesh() {

    // Allocate memory for vertices, normals, and other atr(texture coordinates, and indices)
    GLfloat* vertices = new GLfloat[CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6 * 4 * 3];  // 3 components per vertex, 6 faces per block
    GLuint* indices = new GLuint[CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6 * 6];     // 6 vertices per face, 6 faces per block

    GLint vcount = 0;
    GLint icount = 0;

    int baseVertex = 0;
    int baseIndex = 0;

    std::cout << "PreCreateMEsh" << std::endl;
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int y = 0; y < CHUNK_SIZE_Y; y++) {
            for (int z = 0; z < CHUNK_SIZE_Z; z++) {
                //PerBLock
                if (blocks[x][y][z].ID != BlockType::AIR) {


                    for (int f = 0; f < 6; f++) { //Loop through Faces
                        for (int v = 0; v < 4; v++) { // Loop through verticies
                            int off = v * 3;
                            vertices[baseVertex + f * 12 + off] = faces[f].vertices[off] + (x * VERT_OFFSET * 2);
                            vertices[baseVertex + f * 12 + off + 1] = faces[f].vertices[off + 1] + (y * VERT_OFFSET * 2);
                            vertices[baseVertex + f * 12 + off + 2] = faces[f].vertices[off + 2] + (z * VERT_OFFSET * 2);
                            vcount += 3;
                        }
                        for (int i = 0; i < 6; i++) { //Create indices
                            indices[baseIndex + f * 6 + i] = faces[f].indices[i] + (4 * f) + baseVertex / 3;
                            icount += 1;
                        }
                    }
                    baseVertex += 6 * 4 * 3; // 6 faces per block, 4 vertices per face, 3 components per vertex
                    baseIndex += 6 * 6; // 6 faces per block, 6 indices per fac
                    // std::cout << "here" << std::endl;
                }
            }
        }
    }
    std::cout << vcount << std::endl;
    std::cout << icount << std::endl;
    ;

    vao = new VertexArray(vertices, indices, vcount, icount);

    // std::cout << vao << std::endl;

    //initialize mesh VAO here
    delete[] vertices;
    delete[] indices;
    // delete[] tcs;



}

void Chunk::render() {
    Renderer::BLOCK->use();
    glm::mat4 position = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
    Renderer::BLOCK->setMat4("model", position);
    vao->render();
    // std::cout << "TEst" << std::endl;
}




