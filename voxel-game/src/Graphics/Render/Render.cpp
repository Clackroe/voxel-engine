#include "Graphics/Render/Render.h"
#include "Graphics/Shader.h"

Shader* Renderer::BLOCK;

Camera* Renderer::CAMERA;

Renderer::Renderer()
{
    Renderer::BLOCK = new Shader("D:/Dev/voxel-engine/voxel-game/assets/Shaders/Default.vert", "D:/Dev/voxel-engine/voxel-game/assets/Shaders/Default.frag");

    // Renderer::CAMERA = cam;
}


