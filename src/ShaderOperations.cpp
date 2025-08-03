#include "ShaderOperations.h"
#include <iostream>

GLuint ShaderOperations::CompileShader(GLenum type, const char* source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Error compiling shader: " << infoLog << std::endl;
    }
    return shader;
}

GLuint ShaderOperations::CreateShaderProgram(const char* vertexSource, const char* fragmentSource)
{
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Error linking shader program: " << infoLog << std::endl;
    }
    // Clean up shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}
// Função para ler o conteúdo de um arquivo GLSL
std::string ShaderOperations::LoadShaderSourceFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo de shader: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Função para criar o shader program a partir de arquivos
GLuint ShaderOperations::CreateShaderProgramFromFiles(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode = LoadShaderSourceFromFile(vertexPath);
    std::string fragmentCode = LoadShaderSourceFromFile(fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty()) {
        std::cerr << "Erro ao carregar shaders dos arquivos." << std::endl;
        return 0;
    }

    return CreateShaderProgram(vertexCode.c_str(), fragmentCode.c_str());
}