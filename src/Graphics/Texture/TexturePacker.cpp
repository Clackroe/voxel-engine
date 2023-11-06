#include "TexturePacker.h"

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

std::unordered_map<std::string, Block::TextureFormat> Block::TextureMap;
namespace Texture {
    namespace TexturePacker {


        const int16_t textureSize = 16;

        void genTextures() {
            genTextureList();
            genTextureMap();
            genUV();
            writeToFile();
        }



        void genTextureMap() {
            stbi_flip_vertically_on_write(1);

            int dim = (int)ceil((sqrt(textures.size())));
            int width = dim * textureSize;
            int height = dim * textureSize;

            widthOfFile = width;

            unsigned char* pixels = new unsigned char[width * height * 4]; // Initialize with zeroes

            for (TextureData& tex : textures) {
                int w, h, c;
                unsigned char* data = stbi_load(tex.path.c_str(), &w, &h, &c, 0);
                if (w != textureSize || h != textureSize) {
                    // printf("Texture: %s is not 16x16, Skipping\n", tex.path.c_str());
                    continue;
                }
                if (data) {
                    int x = tex.index % dim;
                    int y = tex.index / dim;
                    tex.pos = glm::ivec2(x, y);
                    for (int i = 0; i < textureSize; i++) {
                        for (int j = 0; j < textureSize; j++) {
                            int idx = ((y * textureSize + i) * width + (x * textureSize + j)) * 4;
                            int idx2 = (i * textureSize + j) * 4;
                            pixels[idx] = data[idx2];
                            pixels[idx + 1] = data[idx2 + 1];
                            pixels[idx + 2] = data[idx2 + 2];
                            pixels[idx + 3] = data[idx2 + 3];
                        }
                    }
                    stbi_image_free(data);
                }
                else {
                    printf("Failed to load image: %s\n", tex.path.c_str());
                }

            }
            stbi_write_png((outputPath + "textureMap.png").c_str(), width, height, 4, pixels, width * 4);
            stbi_image_free(pixels);
        }

        void genTextureList() {
            int idx = 0;
            for (auto const& dir_entry : std::filesystem::directory_iterator{ texturesPath }) {
                std::string name = dir_entry.path().filename().string();
                name = dir_entry.path().stem().string();
                // std::cout << idx << ". Processing: " << name << '\n';
                if (dir_entry.path().string().find(".mcmeta") != std::string::npos) {
                    // std::cout << "Skipping Meta: " << name << '\n';
                    continue;
                }
                textures.push_back(TextureData{ name, dir_entry.path().string(),  idx });
                idx += 1;
            }
        }

        void genUV() {
            // printf("WoF: %d\n", widthOfFile);
            float texRatio = 1.0f / widthOfFile;
            for (TextureData& tex : textures) {
                float leftBounds = tex.pos.x * 16;
                float rightBounds = leftBounds + 16;
                float bottomBounds = tex.pos.y * 16;
                float topBounds = bottomBounds + 16;

                tex.uv_TL = glm::vec2((leftBounds)*texRatio, (topBounds)*texRatio);
                tex.uv_TR = glm::vec2((rightBounds)*texRatio, (topBounds)*texRatio);
                tex.uv_BR = glm::vec2((rightBounds)*texRatio, (bottomBounds)*texRatio);
                tex.uv_BL = glm::vec2((leftBounds)*texRatio, (bottomBounds)*texRatio);
            }
        }

        void writeToFile() {
            json j;
            int idx = 1;
            j["Blocks"]["NULL_BLOCK"] = {
                {"UV",{
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f
                    }
                }
            };
            j["Blocks"]["Air"] = {
                {"UV",{
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f
                    }
                }
            };
            for (TextureData& tex : textures) {
                j["Blocks"][tex.name] = {
                    {"UV",{
                        tex.uv_TL.x, tex.uv_TL.y,
                        tex.uv_TR.x, tex.uv_TR.y,
                        tex.uv_BR.x, tex.uv_BR.y,
                        tex.uv_BL.x, tex.uv_BL.y
                        }
                    }
                };
            }
            std::string out = j.dump(4, ' ', false);

            std::ofstream file;
            file.open(outputPath + "textures.json");
            file << out;
            file.close();
        }

        void loadTextures() {
            std::ifstream file(outputPath + "textures.json");

            if (!file.is_open()) {
                std::cerr << "Error opening blocks.json" << std::endl;
                return;
            }

            json j = json::parse(file);
            file.close();

            if (j.find("Blocks") != j.end()) {
                json blocks = j["Blocks"];

                for (auto& block : blocks.items()) {
                    std::string blockName = block.key(); // Get the block name

                    int idx = 0;
                    for (auto& uv : block.value()["UV"].items()) {
                        for (auto& x : uv.value()) {
                            Block::TextureMap[blockName].uv[idx] = x;
                            idx += 1;
                        }
                    }
                }
            }
            else {
                std::cerr << "No 'Blocks' found in the JSON data." << std::endl;
            }
        }


    }
}

