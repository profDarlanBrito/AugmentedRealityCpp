#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class ShaderOperations
{
public:
    // Apenas as declarações das funções
    static GLuint CompileShader(GLenum type, const char* source);
    static GLuint CreateShaderProgram(const char* vertexSource, const char* fragmentSource);
    std::string LoadShaderSourceFromFile(const std::string& filename);
    GLuint CreateShaderProgramFromFiles(const std::string& vertexPath, const std::string& fragmentPath);
};

