#ifndef OPENGLMANIPULATIONS_HPP
#define OPENGLMANIPULATIONS_HPP
#include <glad/glad.h> // Include glad for OpenGL function loading
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderOperations.h"
#include "ConfigManager.h"
#include "Object.hpp"
#include "Camera.h"

//Constants
#ifndef U_MODEL_MATRIX
constexpr const char* U_MODEL_MATRIX = "uModelMatrix";
#endif // !U_MODEL_MATRIX

#ifndef U_PERSPECTIVE_MATRIX
constexpr const char* U_PERSPECTIVE_MATRIX = "uPerspectiveMatrix";
#endif // !U_PERSPECTIVE_MATRIX
#ifndef U_VIEW_MATRIX
constexpr const char* U_VIEW_MATRIX = "uViewMatrix";
#endif // !U_VIEW_MATRIX
#ifndef U_TEXTURE
constexpr const char* U_TEXTURE = "uTexture";
#endif // !U_TEXTURE
#ifndef U_LOAD_TEXTURE
constexpr const char* U_LOAD_TEXTURE = "uLoadTexture";
#endif // !U_LOAD_TEXTURE

class OpenGLManipulations {
public:
	OpenGLManipulations() : cfg(CONFIG_FILE_PATH_NAME),
		modelTranslation(0.0f, 0.0f, 0.0f),
		scaleFactor(1.0f, 1.0f, 1.0f),
		rotationAngle(0.0f),
		cameraTranslation(0.0f, 0.0f, 5.0f),
		modelMatrix(1.0f)
	{
		// Constructor implementation
		running = false; // Initialize running state
	}
	~OpenGLManipulations();
	static void Run();
	glm::mat4 GetModelMatrix() const {
		return modelMatrix;
	}
	void SetModelMatrix(const glm::mat4& newModelMatrix) {
		modelMatrix = newModelMatrix;
	}
private:
	ShaderOperations shaderOps; // Shader operations object
	ConfigManager cfg; // Configuration manager object
	Camera camera; // Camera object for handling camera operations
	std::vector<Object> objects; // Object to be rendered


	bool InitializeSDL();
	void MainLoop();
	bool VertexGPUAlocation();
	void PreDraw();
	void Draw();
	void HandleEvents();
	void CreateGraphicsPipeline(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName, bool debugOn = true);
	SDL_Window* window = nullptr; // SDL window
	SDL_GLContext glContext = nullptr; // OpenGL context
	int windowWidth = 800; // Default window width
	int windowHeight = 600; // Default window height
	// Other private members for OpenGL manipulations can be added here
	GLuint graphicsPipelineShaderProgram = 0; // Shader program ID
	/*
	GLuint vao = 0; // Vertex Array Object ID
	GLuint vbo = 0; // Vertex Buffer Object ID
	GLuint ebo = 0; // Element Buffer Object ID
	GLuint vboColors = 0; // Vertex Buffer Object for colors
	GLuint vboTextures = 0; // Vertex Buffer Object for textures
	GLuint vboNormals = 0; // Vertex Buffer Object for normals	
	*/
	bool debugOn = true; // Flag to enable OpenGL debug output
	glm::vec3 cameraTranslation; // Camera translation
	float rotationAngle; // Rotation angle for the object
	glm::vec3 scaleFactor; // Scale factor for the object
	glm::vec3 modelTranslation; // Model translation
	bool running;
	glm::mat4 modelMatrix;
};
#endif