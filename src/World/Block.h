#pragma once
#include "../Core/core.h"
#include <string>
#include <unordered_map>

//BlockType definitions
enum BlockType {
    AIR,
    GRASS,
    DIRT,
    STONE,
};

struct BlockInfo {
    GLfloat textureSlot[8];
    float hardness;
    bool transparent;
};

inline std::unordered_map<BlockType, BlockInfo> BlockInfoMap = {
    {BlockType::AIR, {{0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f}, 0.0, true}},
    {BlockType::GRASS,{{0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f }, 1.0, false }},
    { BlockType::DIRT, {{0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f}, 1.0, false} },
    { BlockType::STONE, {{0.0f, 1.0f, 0.5f, 1.0f, 0.5f, 0.5f, 0.0f, 0.5f}, 1.0, false} }
};

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
    L = 4,
    R = 5
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
            -VERT_OFFSET, -VERT_OFFSET, -VERT_OFFSET, // 4
            -VERT_OFFSET,  VERT_OFFSET, -VERT_OFFSET, // 5
             VERT_OFFSET,  VERT_OFFSET, -VERT_OFFSET, // 6
             VERT_OFFSET, -VERT_OFFSET, -VERT_OFFSET, // 7
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
    // Left Face
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
    // Right Face
    {
        // pos
        {
               VERT_OFFSET, -VERT_OFFSET, -VERT_OFFSET, // 20
               VERT_OFFSET,  VERT_OFFSET, -VERT_OFFSET, // 23
               VERT_OFFSET,  VERT_OFFSET,  VERT_OFFSET, // 22
               VERT_OFFSET, -VERT_OFFSET,  VERT_OFFSET, // 21
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
