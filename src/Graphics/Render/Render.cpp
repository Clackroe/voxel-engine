#include "Render.h"
#include "../Shader.h"
#include "BlockRender.h"

Shader* Renderer::BLOCK;
BlockRender* Renderer::blkRender;

Camera* Renderer::CAMERA;

Renderer::Renderer(Camera* cam)
{
    Renderer::BLOCK = new Shader("src/Shaders/Default.vert", "src/Shaders/Default.frag");
    Renderer::blkRender = new BlockRender();

    Renderer::CAMERA = cam;
}

void Renderer::renderBlock(glm::vec3 worldPos)
{
    BlockRender::render(worldPos, CAMERA->getViewMatrix());
}
