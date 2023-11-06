#include "Graphics/Texture/Texture.h"

namespace Texture {

    void GENERATE_DATA() {
        TexturePacker::genTextures();
    }

    void LOAD_DATA() {
        TexturePacker::loadTextures();
    }
}