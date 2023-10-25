#include "BlockRender.h"
#include "Render.h"


float BlockRender::VOXEL_SIZE;
float BlockRender::VERT_OFFSET;

GLfloat BlockRender::VERTICES[8 * 3];
GLuint BlockRender::INDICES[6 * 6];

GLfloat verts[8 * 3] = {
               -1.0f, -1.0f,  1.0f,
                1.0f, -1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
               -1.0f,  1.0f,  1.0f,
               -1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f,  1.0f, -1.0f,
               -1.0f,  1.0f, -1.0f
};;
GLuint ind[6 * 6] = {
            0, 1, 2, 2, 3, 0,
            3, 2, 6, 6, 7, 3,
            7, 6, 5, 5, 4, 7,
            4, 0, 3, 3, 7, 4,
            0, 1, 5, 5, 4, 0,
            1, 5, 6, 6, 2, 1
};

VertexArray* BlockRender::vao;

BlockRender::BlockRender() {
    BlockRender::VOXEL_SIZE = 1.0f;
    BlockRender::VERT_OFFSET = VOXEL_SIZE / 2;
    //Dumb, yes I know...
    for (int i = 0; i < 24; i++) {
        BlockRender::VERTICES[i] = verts[i] * VERT_OFFSET;
    }
    for (int j = 0; j < 24; j++) {
        BlockRender::INDICES[j] = ind[j];
    }



    BlockRender::vao = new VertexArray(VERTICES, INDICES, 8 * 3, 6 * 6);




}

void BlockRender::render(glm::vec3 pos, glm::mat4 view)
{
    Renderer::BLOCK->use();
    glm::mat4 position = glm::translate(glm::mat4(1.0f), pos);
    Renderer::BLOCK->setMat4("model", position);
    Renderer::BLOCK->setMat4("view", view);
    vao->render();
}