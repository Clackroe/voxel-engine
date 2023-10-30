#pragma once
#include <glm/glm.hpp>
#include "../Shader.h"
#include "../VertexArray.h"
#include "../../player/camera.h"

class Renderer {

public:
    static Shader* BLOCK;
    static Camera* CAMERA;

    Renderer(Camera* cam);





};