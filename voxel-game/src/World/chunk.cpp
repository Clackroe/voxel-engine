#include "World/chunk.h"
#include <cstdlib> 
#include "FastNoise.h"


static float mapRange(std::pair<int, int> a, std::pair<int, int> b, float inVal);

Chunk::Chunk(glm::vec2 position)
{
    this->pos = position;

    // std::cout << "INITIALIZING CHUNK" << std::endl;

    blocks.resize(CHUNK_SIZE_X, std::vector<std::vector<BlockData>>(CHUNK_SIZE_Y, std::vector<BlockData>(CHUNK_SIZE_Z, { BlockData({Block::BlockType::AIR}) })));
    test();

    // printf("Generating Chunk\n");
    // FastNoiseLite noise;
    // noise.SetFrequency(0.001f);
    // noise.SetFractalGain(0.07);
    // noise.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);

    int seed = 9828763;

    FastNoiseLite noise;
    noise.SetSeed(seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);

    float defFreq = 0.001f;
    float defAmp = 0.005f;

    noise.SetFrequency(defFreq);
    noise.SetFractalGain(defAmp);


    float perlinFreq = 0.02f;
    float perlinAmp = 0.02f;
    FastNoiseLite perlinNoise;
    perlinNoise.SetFrequency(perlinFreq);
    perlinNoise.SetFractalGain(perlinAmp);
    perlinNoise.SetSeed(seed);
    perlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

    //Different noise type
    FastNoiseLite noise2;
    noise2.SetSeed(seed);
    noise2.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    noise2.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);

    float defFreq2 = 0.001f;
    float defAmp2 = 0.005f;

    noise2.SetFrequency(defFreq2);
    noise2.SetFractalGain(defAmp2);

    FastNoiseLite noise3;
    noise3.SetSeed(seed);
    noise3.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
    noise3.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);

    float defFreq3 = 0.02f;
    float defAmp3 = 0.03f;

    noise3.SetFrequency(defFreq3);
    noise3.SetFractalGain(defAmp3);



    int waterLevel = 85;
    float blendFactor = 0.3f;

    int offset = 350;

    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {


            float gen = mapRange(std::make_pair(-1, 1), std::make_pair(0, 1), noise.GetNoise((float)(CHUNK_SIZE_Z * pos.y + z + offset), (float)(CHUNK_SIZE_X * pos.x + x + offset)));
            float perlinGen = mapRange(std::make_pair(-1, 1), std::make_pair(0, 1), perlinNoise.GetNoise((float)(CHUNK_SIZE_Z * pos.y + z + offset), (float)(CHUNK_SIZE_X * pos.x + x + offset)));
            float noise2Gen = mapRange(std::make_pair(-1, 1), std::make_pair(0, 1), noise2.GetNoise((float)(CHUNK_SIZE_Z * pos.y + z + offset), (float)(CHUNK_SIZE_X * pos.x + x + offset)));
            float noise3Gen = mapRange(std::make_pair(-1, 1), std::make_pair(0, 1), noise3.GetNoise((float)(CHUNK_SIZE_Z * pos.y + z + offset), (float)(CHUNK_SIZE_X * pos.x + x + offset)));

            // Combine different noise functions (you can experiment with how to blend them)
            float finalGen = (gen * blendFactor + (perlinGen * blendFactor) + noise2Gen * blendFactor + noise3Gen * blendFactor * 2) / 2.0f;


            int height = (int)(finalGen * CHUNK_SIZE_Y) + 20;
            // float gen = mapRange(std::make_pair(-1, 1), std::make_pair(0, 1), noise.GetNoise((float)z, (float)x));
            // int height = (int)(gen * CHUNK_SIZE_Y);

            for (int y = 0; y < std::max(waterLevel, height); y++) {
                if (y < waterLevel && y > height) {
                    blocks[x][y][z].ID = Block::BlockType::WATER;
                }
                else {

                    if (y == 0) {
                        blocks[x][y][z].ID = Block::BlockType::BEDROCK;
                    }
                    else if (y < height - 4) {
                        blocks[x][y][z].ID = Block::BlockType::STONE;
                    }
                    else if (y < height - 1) {
                        blocks[x][y][z].ID = Block::BlockType::DIRT;
                    }
                    else {
                        // Add variation to the surface
                        float surfaceVariation = noise.GetNoise((float)z, (float)x) * 0.5f + 0.5f;
                        if (surfaceVariation > 0.5f) {
                            blocks[x][y][z].ID = Block::BlockType::GRASS;
                        }


                        else {
                            blocks[x][y][z].ID = Block::BlockType::GRASS;
                        }
                    }
                }
            }
        }
    }

    // printf("Generating Mesh\n");

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

                    Block::BlockInfo blockInfo = Block::BlockInfoMap[blocks[x][y][z].ID];
                    for (int f = 0; f < 6; f++) {
                        Block::TextureFormat FaceToRender;

                        switch (f)
                        {
                        case Block::FaceIndex::TOP:
                            if (canRender(x, y + 1, z, blocks[x][y][z]) == -1) {
                                continue;
                            }
                            FaceToRender = Block::TextureMap[blockInfo.TOP];
                            break;
                        case Block::FaceIndex::BOTTOM:
                            if (canRender(x, y - 1, z, blocks[x][y][z]) == -1) {
                                continue;
                            }
                            FaceToRender = Block::TextureMap[blockInfo.BOTTOM];
                            break;
                        case Block::FaceIndex::FRONT:
                            if (canRender(x, y, z + 1, blocks[x][y][z]) == -1) {
                                continue;
                            }
                            FaceToRender = Block::TextureMap[blockInfo.FRONT];
                            break;
                        case Block::FaceIndex::BACK:
                            if (canRender(x, y, z - 1, blocks[x][y][z]) == -1) {
                                continue;
                            }
                            FaceToRender = Block::TextureMap[blockInfo.BACK];
                            break;
                        case Block::FaceIndex::L:
                            if (canRender(x + 1, y, z, blocks[x][y][z]) == -1) {
                                continue;
                            }
                            FaceToRender = Block::TextureMap[blockInfo.LEFT];
                            break;
                        case Block::FaceIndex::R:
                            if (canRender(x - 1, y, z, blocks[x][y][z]) == -1) {
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
                            texCoords[baseTex + t] = FaceToRender.uv[t];
                        }


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


int Chunk::canRender(int x, int y, int z, BlockData block) {
    if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE_X || y >= CHUNK_SIZE_Y || z >= CHUNK_SIZE_Z || (block.ID == 8 && blocks[x][y][z].ID == block.ID)) {
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
    GLint swizzleParams[4] = { GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA };
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleParams);


    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ONE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load("D:/Dev/voxel-engine/voxel-game/assets/textureMap.png", &width, &height, &nrChannels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    // glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);


    // qexture(GL_TEXTURE0);

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



