#pragma once
#include "Core/core.h"
#include "nlohmann/json.hpp"
#include "stb_image_write.h"
#include "stb_image.h"
#include "World/Block.h"
/*
Texture Location(x, y) "In The Main Texture File"

 -------------------
 | (0, 1) | (1, 1) |
 | ----------------|
 | (0, 0) | (1, 0) |
 -------------------


Texture Coords To Load In Shader
(LB, TB), (RB, TB)
(LB, BB), (RB, BB)

Combined:Txtr Ratio 'R' = WidthOfFile / WidthOfTexture

LB = x * R      BB = y * R
RB = LB + R     TB = BB + R

*/
namespace Texture {
    namespace TexturePacker {
        using json = nlohmann::json;

        struct TextureData {
            std::string name;
            std::string path;
            int index;
            glm::ivec2 pos;
            glm::vec2 uv_TL; // Top Left
            glm::vec2 uv_TR; // Top Right
            glm::vec2 uv_BR; // Bottom Right
            glm::vec2 uv_BL; // Bottom Left
        };

        void genTextureList();
        void genTextures();
        void genTextureMap();
        void genUV();
        void writeToFile();
        void loadTextures();


        inline std::filesystem::path texturesPath{ "D:/Dev/voxel-engine/voxel-game/assets/block" };
        inline std::string outputPath = "D:/Dev/voxel-engine/voxel-game/assets";
        inline std::vector<TextureData> textures;
        inline int widthOfFile;


    }
}