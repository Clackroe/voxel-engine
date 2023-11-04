#include "chunk.h"
#include <cstdlib> 


static float mapRange(std::pair<int, int> a, std::pair<int, int> b, float inVal);

Chunk::Chunk(glm::vec2 position)
{
    this->pos = position;

    // std::cout << "INITIALIZING CHUNK" << std::endl;

    blocks.resize(CHUNK_SIZE_X, std::vector<std::vector<BlockData>>(CHUNK_SIZE_Y, std::vector<BlockData>(CHUNK_SIZE_Z, { BlockData({Block::BlockType::AIR}) })));
    test();

    // for (int x = 0; x < CHUNK_SIZE_X; x++) {
    //     for (int z = 0; z < CHUNK_SIZE_Z; z++) {
    //         int h = rand() % CHUNK_SIZE_Y - 187;

    //         for (int y = 0; y < h; y++) {
    //             blocks[x][y][z] = { Block({BlockType::DIRT}) };
    //         }

    //     }
    // }



    // for (int y = 0; y < 5; ++y)
    // {
    //     for (int x = 0; x < 5; ++x)
    //     {


    //         std::cout << noise << '\t';
    //     }

    //     std::cout << '\n';
    // }
    SimplexNoise gen;
    int32_t incSize = 1000;
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {
            float height = mapRange(std::make_pair(-1, 1), std::make_pair(0, CHUNK_SIZE_Y - 1), gen.fractal(10, (CHUNK_SIZE_X * pos.x + x) / incSize, (CHUNK_SIZE_Z * pos.y + z) / incSize));
            // float height = SimplexNoise::noise(CHUNK_SIZE_X * pos.x + x, CHUNK_SIZE_Z * pos.y + z);
            // std::cout << "Height: " << height << std::endl;
            for (int y = 0; y < height; y++) {
                if (y < height - 6) {
                    blocks[x][y][z] = { BlockData({Block::BlockType::STONE}) };
                    continue;
                }
                if (y < height - 1) {
                    blocks[x][y][z] = { BlockData({ Block::BlockType::DIRT}) };
                    continue;
                }


                blocks[x][y][z] = { BlockData({Block::BlockType::GRASS}) };
            }
        }
    }




    // for (int x = 0; x < CHUNK_SIZE_X; x++) {
    //     for (int y = 0; y < CHUNK_SIZE_Y; y++) {
    //         for (int z = 0; z < CHUNK_SIZE_Z; z++) {
    //             // if (y >= 4) {
    //             //     blocks[x][y][z] = { Block({BlockType::AIR}) };
    //             // }
    //             // // else if (x < 4 && y > 2) {
    //             // //     blocks[x][y][z] = { Block({BlockType::AIR}) };
    //             // // }
    //             // else {
    //             //     blocks[x][y][z] = { Block({BlockType::DIRT}) };
    //             // }

    //         }
    //     }
    // }
    // blocks[2][150][2] = { Block({BlockType::DIRT}) };
    // blocks[3][150][3] = { Block({BlockType::DIRT}) };
    // blocks[2][0][0] = { Block({BlockType::DIRT}) };
    // blocks[0][0][0] = { Block({BlockType::DIRT}) };
    // blocks[0][1][0] = { Block({BlockType::DIRT}) };
    // std::cout << "FINISHED INITIALIZING CHUNK" << std::endl;

    createMesh();


}

Chunk::~Chunk()
{
    delete[] vertices;
    delete[] indices;
    delete[] texCoords;
    delete vao;
}

void Chunk::createMesh() {

    // Allocate memory for vertices, normals, and other atr(texture coordinates, and indices)
    vertices = new GLfloat[CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6 * 4 * 3];  // 3 components per vertex, 6 faces per block
    indices = new GLuint[CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6 * 6];     // 6 vertices per face, 6 faces per block
    texCoords = new GLfloat[CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 8 * 6];

    GLint vcount = 0;
    GLint icount = 0;

    int baseVertex = 0;
    int baseIndex = 0;
    int baseTex = 0;

    // std::cout << "Creating Mesh" << std::endl;
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int y = 0; y < CHUNK_SIZE_Y; y++) {
            for (int z = 0; z < CHUNK_SIZE_Z; z++) {
                //PerBLock
                if (blocks[x][y][z].ID != 0) { //Air
                    // int fCursor = 0;

                    // int f = ; // Face to Render

                    Block::BlockInfo blockInfo = Block::BlockInfoMap[blocks[x][y][z].ID];
                    for (int f = 0; f < 6; f++) {
                        Block::TextureFormat FaceToRender;

                        switch (f)
                        {
                        case Block::FaceIndex::TOP:
                            if (canRender(x, y + 1, z) == -1) {
                                continue;
                            }
                            FaceToRender = Block::TextureMap[blockInfo.TOP];
                            break;
                        case Block::FaceIndex::BOTTOM:
                            if (canRender(x, y - 1, z) == -1) {
                                continue;
                            }
                            FaceToRender = Block::TextureMap[blockInfo.BOTTOM];
                            break;
                        case Block::FaceIndex::FRONT:
                            if (canRender(x, y, z + 1) == -1) {
                                continue;
                            }
                            FaceToRender = Block::TextureMap[blockInfo.FRONT];
                            break;
                        case Block::FaceIndex::BACK:
                            if (canRender(x, y, z - 1) == -1) {
                                continue;
                            }
                            FaceToRender = Block::TextureMap[blockInfo.BACK];
                            break;
                        case Block::FaceIndex::L:
                            if (canRender(x + 1, y, z) == -1) {
                                continue;
                            }
                            FaceToRender = Block::TextureMap[blockInfo.LEFT];
                            break;
                        case Block::FaceIndex::R:
                            if (canRender(x - 1, y, z) == -1) {
                                continue;
                            }
                            FaceToRender = Block::TextureMap[blockInfo.RIGHT];
                            break;
                        default:
                            break;
                        }


                        for (int v = 0; v < 4; v++) { // Loop through verticies

                            int off = v * 3;
                            vertices[baseVertex + off] = Block::faces[f].vertices[off] + (x * Block::VERT_OFFSET * 2);
                            vertices[baseVertex + off + 1] = Block::faces[f].vertices[off + 1] + (y * Block::VERT_OFFSET * 2);
                            vertices[baseVertex + off + 2] = Block::faces[f].vertices[off + 2] + (z * Block::VERT_OFFSET * 2);
                            vcount += 3;
                        }
                        for (int i = 0; i < 6; i++) { //Create indices
                            indices[baseIndex + i] = Block::faces[f].indices[i] + (0) + baseVertex / 3;
                            icount += 1;
                        }
                        for (int t = 0; t < 8; t++) {
                            texCoords[baseTex + t] = FaceToRender.uv[t];//faces[f].texCoords[t];A
                            // printf("%f \n", texCoords[baseTex + t]);
                            // std::cout << texCoords[baseTex + f * 8 + t] << std::endl;

                        }
                        // std::cout << std::endl;


                        baseVertex += 4 * 3; // 6 faces per block, 4 vertices per face, 3 components per vertex
                        baseIndex += 6; // 6 faces per block, 6 indices per fac
                        baseTex += 8;

                    }
                }
            }
        }
    }
    vao = new VertexArray(vertices, indices, texCoords, vcount, icount);

}


int Chunk::canRender(int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE_X || y >= CHUNK_SIZE_Y || z >= CHUNK_SIZE_Z) {
        return -2; // Out of bounds, return -1
    }
    else if (Block::BlockInfoMap[blocks[x][y][z].ID].transparent == false) {
        return -1;

    }
    else {
        return blocks[x][y][z].ID; // Return the BlockType ID

    }
}


void Chunk::render() {
    Renderer::BLOCK->use();
    glm::mat4 position = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x * CHUNK_SIZE_X, 0.0, pos.y * CHUNK_SIZE_Z));
    Renderer::BLOCK->setMat4("model", position);
    // GLuint tex0 = glGetUniformLocation(Renderer::BLOCK->ID, "tex");
    Renderer::BLOCK->setInt("tex", 0);


    vao->render();
    // std::cout << "TEst" << std::endl;
}

void Chunk::test() {

    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load("/home/clack/Documents/SideProjs/voxel-engine/src/assets/textureMap.png", &width, &height, &nrChannels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);


    // glActiveTexture(GL_TEXTURE0);

    // glBindTexture(GL_TEXTURE_2D, texture);
}


static float mapRange(std::pair<int, int> a, std::pair<int, int> b, float inVal)
{
    float inValNorm = inVal - a.first;
    float aUpperNorm = a.second - a.first;
    float normPosition = inValNorm / aUpperNorm;

    float bUpperNorm = b.second - b.first;
    float bValNorm = normPosition * bUpperNorm;
    float outVal = b.first + bValNorm;

    return outVal;


}



