#pragma once
#include <iostream>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/type_ptr.hpp> // Adicione esta linha no início do arquivo, junto com os outros includes
#include <Camera.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "ShaderOperations.h"   
#include "Object.hpp" // Inclua o cabeçalho do objeto que você deseja manipular
#pragma comment(lib, "SDL3.lib")
#include <SDL3_image/SDL_image.h> // Uncomment if you need to load images/textures
#include "ConfigManager.h" // Include your configuration manager header
// Defina aqui as declarações necessárias para o seu aplicativo de Realidade Aumentada.

using namespace std;


class AugmentedReality
{
public:
    ShaderOperations shaderOps; // Assuming you have a ShaderOperations class for shader management
    Camera camera; // Assuming you have a Camera class for camera operations
	Object object; // Assuming you have an Object class for 3D objects
    ConfigManager cfg;

    AugmentedReality();

    ~AugmentedReality();

    void Run();

    void GetOpenGLVersionInfo();

    void VertexSpecification();

    bool InitializeSDL();


	// Getters and setters
    SDL_Window* GetWindow() const { return window; }
    SDL_GLContext GetGLContext() const { return glContext; }
    int GetWindowWidth() const { return windowWidth; }
    int GetWindowHeight() const { return windowHeight; }
    bool IsRunning() const { return running; }
	void SetRunning(bool value) { running = value; }
	void SetWindowSize(int width, int height) { windowWidth = width; windowHeight = height; }
    void SetWindow(SDL_Window* win) { window = win; }
	void SetGLContext(SDL_GLContext context) { glContext = context; }
    void HandleEvents();
    void CreateGraphicsPipeline(const std::string vertexShaderFileName, const std::string fragmentShaderFileName, bool debugOn = true);
    void PreDraw(glm::mat4& modelMatrix);
    void Draw();

private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
    int windowWidth = 800;
    int windowHeight = 600;
	bool running = true;
	GLuint vao = 0; // Vertex Array Object
    GLuint vbo = 0; // Vertex Buffer Object
	GLuint ebo = 0; // Element Buffer Object (if needed)
    GLuint vboColors = 0; // Vertex Buffer Object for colors (if needed)
	GLuint vboTextures = 0; // Vertex Buffer Object for textures (if needed)
	GLuint graphicsPipelineShaderProgram = 0; // Graphics Pipeline Object
    int verticesSize = 0; // Size of vertices, if needed
    float offsetZ = 0.0f; // Offset for Y-axis, if needed
    float rotationAngle = 0.0f; // Rotation angle, if needed
    float scaleFactor = 1.0f; // Scale factor, if needed
    glm::mat4 modelMatrix = glm::mat4(1.0f); // Model matrix for transformations
};