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


unsigned int SHADER_PROGRAM;


World::World() {

    SHADER_PROGRAM = compileShaders("src/Shaders/DefaultVertex.shader", "src/Shaders/DefaultFrag.shader");



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
}

World::~World() {

}


void World::render() {


    // float time = glfwGetTime();
    // float greenValue = (sin(time) / 2.0f) + 0.5f;
    // int vertexColorLocation = glGetUniformLocation(SHADER_PROGRAM, "color");

    glUseProgram(SHADER_PROGRAM);
    // glUniform4f(vertexColorLocation, 1.0, greenValue, 1.0, 1.0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void World::update() {

}