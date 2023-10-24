#pragma once
#include "../Graphics/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Graphics/VertexArray.h"

class Block {


public:
    Block(float x, float y, float z);
    VertexArray* vao;
    void render(glm::mat4 view);

    Shader* shader;
private:
    glm::vec3 worldPos;





};