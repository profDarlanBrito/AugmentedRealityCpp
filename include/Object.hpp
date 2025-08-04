#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <vector>
#include <glad/glad.h> // Include glad for OpenGL function loading
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_surface.h>
#include <tiny_obj_loader.h>

class Object {
public:
	Object() {
		// Constructor implementation
		verticesSize = 0; // Initialize vertices size
		textureID = 0; // Initialize texture ID
	}
	~Object() {
		// Destructor implementation
	}
	void Initialize() {
		// Initialization code
	}
	void Render() {
		// Rendering code
	}
	void Update() {
		// Update logic
	}
	std::vector<GLfloat> GetVertices() const {
		return vertices;
	}
	void SetVertices(const std::vector<GLfloat>& newVertices) {
		vertices = newVertices;
		verticesSize = newVertices.size();
	}
	void SetVerticesColors(const std::vector<GLfloat>& newColors) {
		if (newColors.size() != vertices.size()) {
			std::cerr << "Error: Colors size must match vertices size." << std::endl;
			return; // Handle error appropriately
		}
		verticesColors = newColors;
	}
	void SetIndices(const std::vector<GLuint>& newIndices) {
		if (vertices.size() == 0) {
			std::cerr << "Error: Vertices must be set before setting indices." << std::endl;
			return; // Handle error appropriately
		}
		indices = newIndices;
	}
	void SetVertexSpecification(const std::vector<GLfloat>& newVertices, const std::vector<GLfloat>& newColors, const std::vector<GLuint>& newIndices) {
		SetVertices(newVertices);
		SetVerticesColors(newColors);
		SetIndices(newIndices);
		verticesSize = newVertices.size(); // Update vertices size
	}
	std::vector<GLfloat> GetVerticesColors() const {
		return verticesColors;
	}
	std::vector<GLuint> GetIndices() const {
		return indices;
	}
	std::vector<GLfloat> GetVerticesNormals() const {
		return verticesNormals; // Optional, if you need normals
	}
	std::vector<GLfloat> GetVerticesTextureCoords() const {
		return verticesTextureCoords; // Optional, if you need texture coordinates
	}
	GLuint LoadTexture(const std::string& filePath, SDL_Window* window);
	void TestTexture();
	GLuint GetTextureID() const {
		return textureID; // Return the texture ID if needed
	}
	void SetTextureCoords(const std::vector<GLfloat>& newTextureCoords) {
		verticesTextureCoords = newTextureCoords; // Set texture coordinates if needed
	}
	GLuint GetVerticesSize() const {
		return verticesSize; // Return the size of the vertices vector
	}
	bool IsTextureLoaded() const {
		return textureLoaded; // Return whether the texture is loaded
	}
	bool LoadFromOBJ(const std::string& filePath);
private:
	// Private member variables and methods
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> verticesColors;
	std::vector<GLuint> indices;
	std::vector<GLfloat> verticesNormals; // Optional, if you need normals
	std::vector<GLfloat> verticesTextureCoords; // Optional, if you need texture coordinates
	GLuint textureID; // Texture ID for OpenGL
	GLuint verticesSize; // Size of the vertices vector
	std::string textureFilePath; // File path for the object file
	bool textureLoaded = false; // Flag to check if texture is loaded
};

#endif // OBJECT_HPP