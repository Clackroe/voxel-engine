#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include <glad/glad.h>


class Shader {

public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragPath);

    void use();

    void setBool(const std::string& name, bool value) const;
    void setFloat(const std::string& name, float value) const;
    void setInt(const std::string& name, int value) const;
};