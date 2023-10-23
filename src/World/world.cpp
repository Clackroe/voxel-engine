#include "world.h"




unsigned int compileShaders(const char* vertex, const char* frag) {

    std::string vShadSrc = FileUtils::read_file(vertex);
    std::string fShadSrc = FileUtils::read_file(frag);

    const char* vertShad = vShadSrc.c_str();
    const char* fragShad = fShadSrc.c_str();

    int result;
    char infoLog[512];

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertShad, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

    if (!result) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERRO WITH VERT SHADER" << std::endl;
    }

    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShad, NULL);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);

    if (!result) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR WITH FRAG SHADER COMPILE" << std::endl;
    }

    //Link Shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);

    if (!result) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR LINKING PROGRAM" << std::endl;

    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    return shaderProgram;



}




World::World(Player* plyr)
{
    std::cout << "PREFIRE" << std::endl;
    SHADER_PROGRAM = new Shader("src/Shaders/Default.vert", "src/Shaders/Default.frag");
    player = plyr;
    // cam = new Camera();


    //projections

       // std::cout << "FIRED" << std::endl;
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f// bottom right
        - 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// bottom left
        -0.5f,  0.5f, 0.0f,   0.5f, 0.5f, 0.5f// top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
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

    // std::cout << "Render" << std::endl;

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    // unsigned int transformLoc = glGetUniformLocation(SHADER_PROGRAM->ID, "transform");
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    // glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 100.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));


    // glm::mat4 view = glm::mat4(1.0f);
    // // note that we're translating the scene in the reverse direction of where we want to move
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
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
    // float time = glfwGetTime();
    //
    // float greenValue = (sin(time) / 2.0f) + 0.5f;
    // int vertexColorLocation = glGetUniformLocation(SHADER_PROGRAM, "color");

    // glUniform4f(vertexColorLocation, 1.0, greenValue, 1.0, 1.0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    // std::cout << "PostDraw" << std::endl;

}

void World::update(float deltaTime) {

    player->processInput(deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //     cam->processKeyboardInput(FORWARD, 1.0);
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //     cam->processKeyboardInput(BACKWARD, 1.0);
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //     cam->processKeyboardInput(LEFT, 1.0);
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     cam->processKeyboardInput(RIGHT, 1.0);


}

// // glfw: whenever the mouse moves, this callback is called
// // -------------------------------------------------------
// void mouse_callback(GLFWwindow* window, double xposIn, double yposIn, Camera* cam)
// {
    // float xpos = static_cast<float>(xposIn);
//     float ypos = static_cast<float>(yposIn);

//     if (firstMouse)
//     {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }

//     float xoffset = xpos - lastX;
//     float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

//     lastX = xpos;
//     lastY = ypos;

//     cam->processMouseInput(xoffset, yoffset);
// }

// // glfw: whenever the mouse scroll wheel scrolls, this callback is called
// // ----------------------------------------------------------------------
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
//     camera.ProcessMouseScroll(static_cast<float>(yoffset));
// }