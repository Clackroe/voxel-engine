#include <fstream>
#include <glad/glad.h>
#include "../utils/FileUtils.h"
#include <string>
#include "glm/glm.hpp"
#include <GLFW/glfw3.h>
class World {

public:
    World();
    ~World();

    void render();
    void update();



};