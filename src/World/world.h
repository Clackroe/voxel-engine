#include <fstream>
#include <glad/glad.h>
#include "../utils/FileUtils.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include"../Graphics/Shader.h"
#include "../player/camera.h"
#include "../player/player.h"
class World {

public:
    World(Player* plyr);
    ~World();

    Shader* SHADER_PROGRAM;
    Player* player;
    void render(float deltaTime);
    void update(float deltaTime);



};