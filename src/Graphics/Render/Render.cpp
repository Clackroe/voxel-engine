#include "Render.h"
#include "../Shader.h"

Shader* Renderer::BLOCK;

Camera* Renderer::CAMERA;

Renderer::Renderer()
{
    Renderer::BLOCK = new Shader("/home/clack/Documents/SideProjs/voxel-engine/src/Shaders/Default.vert", "/home/clack/Documents/SideProjs/voxel-engine/src/Shaders/Default.frag");

    // Renderer::CAMERA = cam;
}


