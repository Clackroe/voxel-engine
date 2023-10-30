#include "Render.h"
#include "../Shader.h"

Shader* Renderer::BLOCK;

Camera* Renderer::CAMERA;

Renderer::Renderer(Camera* cam)
{
    Renderer::BLOCK = new Shader("src/Shaders/Default.vert", "src/Shaders/Default.frag");

    Renderer::CAMERA = cam;
}


