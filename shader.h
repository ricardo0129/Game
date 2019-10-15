#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int shaderID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    unsigned int reference();
    unsigned int uniformLocation(const char* name);
    void uniformMat4(unsigned int reference, glm::mat4 matrix);
  
private:
};
  
#endif