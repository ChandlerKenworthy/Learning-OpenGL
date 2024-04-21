#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // Required to get the OpenGL headers
#include <iostream>
#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>

class Shader {
    public:
    unsigned int ID; // program ID
    Shader(const char* vertexPath, const char* fragmentPath);
    void use() { glUseProgram(ID); }

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif