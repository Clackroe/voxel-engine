#pragma once
#include <glm/glm.hpp>
#include "../VertexArray.h"


class BlockRender {

public:
    BlockRender();
    static void render(glm::vec3 pos, glm::mat4 view);
    static float VOXEL_SIZE;
    static float VERT_OFFSET;


private:

    static GLfloat VERTICES[8 * 3];
    static GLuint INDICES[6 * 6];
    static VertexArray* vao;






};