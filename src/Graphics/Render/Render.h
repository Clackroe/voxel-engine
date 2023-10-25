#pragma once
#include <glm/glm.hpp>
#include "../Shader.h"
#include "../VertexArray.h"
#include "../../player/camera.h"
#include "BlockRender.h"

class Renderer {

public:
    static Shader* BLOCK;
    static BlockRender* blkRender;
    static Camera* CAMERA;

    Renderer(Camera* cam);



    static void renderBlock(glm::vec3 worldPos);


private:
    const float VOXEL_SIZE = 1.0f;
    const float VERT_OFFSET = VOXEL_SIZE / 2;


};