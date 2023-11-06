#pragma once
#include "../Core/core.h"
#include <string>
#include <unordered_map>
#include "../vendor/JSON/json.hpp"
namespace Block {
    // BlockType definitions
    enum BlockType {
        NULL_BLOCK = -1,
        AIR = 0,
        STONE = 1,
        GRASS = 2,
        DIRT = 3,
        COBBLESTONE = 4,
        OAK_PLANKS = 5,
        BEDROCK = 6,
        SAND = 7,
        WATER = 8,
    };

    struct TextureFormat {
        GLfloat uv[8];
    };

    struct BlockInfo {
        float hardness;
        bool transparent;
        std::string TOP;
        std::string BOTTOM;
        std::string FRONT;
        std::string BACK;
        std::string LEFT;
        std::string RIGHT;
    };
    extern std::unordered_map<std::string, TextureFormat> TextureMap;
    inline std::unordered_map<BlockType, BlockInfo> BlockInfoMap;
    void loadBlockInfo();


    //Face Rendering Information
    struct BlockFace {
        GLfloat vertices[3 * 4];
        GLint indices[6];
        GLfloat normals[3 * 4];
        GLfloat texCoords[2 * 4];
    };

    inline float VERT_OFFSET = 0.5f;

    enum FaceIndex {
        FRONT = 0,
        BACK = 1,
        TOP = 2,
        BOTTOM = 3,
        R = 4,
        L = 5

    };

    inline BlockFace faces[6] = {
        // Front Face
        {
            // pos
            {
                -VERT_OFFSET, -VERT_OFFSET,  VERT_OFFSET, // 0
                 VERT_OFFSET, -VERT_OFFSET,  VERT_OFFSET, // 1
                 VERT_OFFSET,  VERT_OFFSET,  VERT_OFFSET, // 2
                -VERT_OFFSET,  VERT_OFFSET,  VERT_OFFSET, // 3
            },

            // indices
            {0, 1, 2, 2, 3, 0},

            // normals
            {
                 0.0f,  0.0f,  1.0f,
                 0.0f,  0.0f,  1.0f,
                 0.0f,  0.0f,  1.0f,
                 0.0f,  0.0f,  1.0f,
            },

            // texCoords
            {
                0.0f, 1.0f,
                0.5f, 1.0f,
                0.5f, 0.5f,
                0.0f, 0.5f,
            }
        },
        // Back Face
        {
            // pos
            {
                 VERT_OFFSET, -VERT_OFFSET, -VERT_OFFSET, // 7
                -VERT_OFFSET, -VERT_OFFSET, -VERT_OFFSET, // 4
                -VERT_OFFSET,  VERT_OFFSET, -VERT_OFFSET, // 5
                 VERT_OFFSET,  VERT_OFFSET, -VERT_OFFSET, // 6
            },

            // indices
            {0, 1, 2, 2, 3, 0},

            // normals
            {
                  0.0f,  0.0f, -1.0f,
                  0.0f,  0.0f, -1.0f,
                  0.0f,  0.0f, -1.0f,
                  0.0f,  0.0f, -1.0f,
            },

            // texCoords
            {
                0.5f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.5f,
                0.5f, 0.5f,
            }
        },
        // Top Face
        {
            // pos
            {
                 -VERT_OFFSET,  VERT_OFFSET, -VERT_OFFSET, // 8
                 -VERT_OFFSET,  VERT_OFFSET,  VERT_OFFSET, // 11
                  VERT_OFFSET,  VERT_OFFSET,  VERT_OFFSET, // 10
                  VERT_OFFSET,  VERT_OFFSET, -VERT_OFFSET, // 9
            },

            // indices
            {0, 1, 2, 2, 3, 0},

            // normals
            {
                   0.0f,  1.0f,  0.0f,
                   0.0f,  1.0f,  0.0f,
                   0.0f,  1.0f,  0.0f,
                   0.0f,  1.0f,  0.0f,
            },

            // texCoords
            {
                0.0f, 0.5f,
                0.5f, 0.5f,
                0.5f, 0.0f,
                0.0f, 0.0f,
            }
        },
        // Bottom Face
        {
            // pos
            {
                  -VERT_OFFSET, -VERT_OFFSET, -VERT_OFFSET, // 12
                   VERT_OFFSET, -VERT_OFFSET, -VERT_OFFSET, // 13
                   VERT_OFFSET, -VERT_OFFSET,  VERT_OFFSET, // 14
                  -VERT_OFFSET, -VERT_OFFSET,  VERT_OFFSET, // 15
            },

            // indices
            {0, 1, 2, 2, 3, 0},

            // normals
            {
                    0.0f, -1.0f,  0.0f,
                    0.0f, -1.0f,  0.0f,
                    0.0f, -1.0f,  0.0f,
                    0.0f, -1.0f,  0.0f,
            },

            // texCoords
            {
                0.0f, 0.5f,
                0.5f, 0.5f,
                0.5f, 0.0f,
                0.0f, 0.0f,
            }
        },
        // Right Face
        {
            // pos
            {
                  -VERT_OFFSET, -VERT_OFFSET, -VERT_OFFSET, // 16
                  -VERT_OFFSET, -VERT_OFFSET,  VERT_OFFSET, // 17
                  -VERT_OFFSET,  VERT_OFFSET,  VERT_OFFSET, // 18
                  -VERT_OFFSET,  VERT_OFFSET, -VERT_OFFSET, // 19
            },

            // indices
            {0, 1, 2, 2, 3, 0},

            // normals
            {
                     -1.0f,  0.0f,  0.0f,
                     -1.0f,   0.0f,  0.0f,
                     -1.0f,   0.0f,  0.0f,
                     -1.0f,   0.0f,  0.0f,
            },

            // texCoords
            {
                0.0f, 0.5f,
                0.5f, 0.5f,
                0.5f, 0.0f,
                0.0f, 0.0f,
            }
        },
        // Left Face
        {
            // pos
            {
                   VERT_OFFSET, -VERT_OFFSET,  VERT_OFFSET, // 21
                   VERT_OFFSET, -VERT_OFFSET, -VERT_OFFSET, // 20
                   VERT_OFFSET,  VERT_OFFSET, -VERT_OFFSET, // 23
                   VERT_OFFSET,  VERT_OFFSET,  VERT_OFFSET, // 22
            },

            // indices
            {0, 1, 2, 2, 3, 0},

            // normals
            {
                      1.0f,   0.0f,   0.0f,
                      1.0f,   0.0f,   0.0f,
                      1.0f,   0.0f,   0.0f,
                      1.0f,   0.0f,   0.0f,
            },

            // texCoords
            {
                0.0f, 0.5f,
                0.5f, 0.5f,
                0.5f, 0.0f,
                0.0f, 0.0f,
            }
          }

    };
}
