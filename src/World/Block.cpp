#include "Block.h"

Block::Block(float x, float y, float z)
{
    const float SIZE = 1.0f;
    const float vertOffset = SIZE / 2;
    worldPos.x = x * SIZE;
    worldPos.y = y * SIZE;
    worldPos.z = z * SIZE;
    GLfloat vertices[8 * 3] = {
           -vertOffset, -vertOffset,  vertOffset,
            vertOffset, -vertOffset,  vertOffset,
            vertOffset,  vertOffset,  vertOffset,
           -vertOffset,  vertOffset,  vertOffset,
           -vertOffset, -vertOffset, -vertOffset,
            vertOffset, -vertOffset, -vertOffset,
            vertOffset,  vertOffset, -vertOffset,
           -vertOffset,  vertOffset, -vertOffset
    };

    GLuint indices[6 * 6] = {
            0, 1, 2, 2, 3, 0,
            3, 2, 6, 6, 7, 3,
            7, 6, 5, 5, 4, 7,
            4, 0, 3, 3, 7, 4,
            0, 1, 5, 5, 4, 0,
            1, 5, 6, 6, 2, 1
    };


    vao = new VertexArray(vertices, indices, 8 * 3, 6 * 6);
    shader = new Shader("src/Shaders/Default.vert", "src/Shaders/Default.frag");
}



void Block::render(glm::mat4 view) {
    shader->use();
    glm::mat4 pos = glm::translate(glm::mat4(1.0f), worldPos);
    shader->setMat4("model", pos);
    shader->setMat4("view", view);
    // shader->("block_color", color);
    vao->render();
}