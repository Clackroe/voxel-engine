#include "Block.h"

namespace Block {
    using json = nlohmann::json;

    void loadBlockInfo() {
        std::ifstream file("/home/clack/Documents/SideProjs/voxel-engine/src/assets/blocks.json");
        json j = json::parse(file);
        file.close();

        if (j.find("Blocks") != j.end()) {
            json blocks = j["Blocks"];

            for (auto& block : blocks.items()) {
                int ID = std::stoi(block.key()); // Get the block name
                printf("Loading %d\n", ID);
                BlockInfoMap[BlockType(ID)] = {
                    block.value()["hardness"].get<float>(),
                    block.value()["transparent"].get<bool>(),
                    block.value()["TOP"].get<std::string>(),
                    block.value()["BOTTOM"].get<std::string>(),
                    block.value()["FRONT"].get<std::string>(),
                    block.value()["BACK"].get<std::string>(),
                    block.value()["LEFT"].get<std::string>(),
                    block.value()["RIGHT"].get<std::string>()
                };
            }
        }
    }

}