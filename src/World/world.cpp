#include "world.h"





World::World(Player* plyr)
{
    std::cout << "PREFIRE" << std::endl;
    SHADER_PROGRAM = new Shader("src/Shaders/Default.vert", "src/Shaders/Default.frag");
    player = plyr;
    // cam = new Camera();


    //projections
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f// bottom right
        - 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// bottom left
        -0.5f,  0.5f, 0.0f,   0.5f, 0.5f, 0.5f// top left 
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 0, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VBO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}

World::~World() {

}


void World::render(float deltaTime) {

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view = player->cam->getViewMatrix();

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


    unsigned int modelLoc = glGetUniformLocation(SHADER_PROGRAM->ID, "model");
    unsigned int viewLoc = glGetUniformLocation(SHADER_PROGRAM->ID, "view");
    unsigned int projectionLoc = glGetUniformLocation(SHADER_PROGRAM->ID, "projection");


    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    SHADER_PROGRAM->use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void World::update(float deltaTime) {

    player->processInput(deltaTime);


}