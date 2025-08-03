#include "Object.hpp"
#include <SDL3/SDL_surface.h>

GLuint Object::LoadTexture(const std::string& filePath, SDL_Window* window)
{
	// Load texture using stb_image or any other image loading library
	int width, height, nrChannels;
	SDL_Surface* surface = nullptr;
	if (filePath.empty()) {
		surface = SDL_LoadBMP(textureFilePath.c_str());
	}
	else {
		surface = SDL_LoadBMP(filePath.c_str());
	}
	if (surface) {
		unsigned char* data = static_cast<unsigned char*>(surface ? surface->pixels : nullptr);
		if (!data) {
			std::cerr << "Failed to load image data from surface." << std::endl;
			SDL_DestroySurface(surface);
			std::exit(EXIT_FAILURE);
		}
		GLenum format;
		if (surface->format == SDL_PIXELFORMAT_RGBA32) {
			format = GL_RGBA;
		} else if (surface->format == SDL_PIXELFORMAT_RGB24) {
			format = GL_RGB;
		} else if (surface->format == SDL_PIXELFORMAT_ARGB32) {
			format = GL_BGRA; // OpenGL expects BGRA format for ARGB
		} else if (surface->format == SDL_PIXELFORMAT_BGR24) {
			format = GL_BGR; // OpenGL expects BGR format for RGB
		} else if (surface->format == SDL_PIXELFORMAT_ABGR32) {
			format = GL_RGBA; // OpenGL expects RGBA format for ABGR
		} else if (surface->format == SDL_PIXELFORMAT_RGB565) {
			format = GL_RGB; // OpenGL expects RGB format for RGB565
		} else if (surface->format == SDL_PIXELFORMAT_RGBA4444) {
			format = GL_RGBA; // OpenGL expects RGBA format for RGBA4444
		} else if (surface->format == SDL_PIXELFORMAT_ARGB1555) {
			format = GL_BGRA; // OpenGL expects BGRA format for ARGB1555
		} else if (surface->format == SDL_PIXELFORMAT_RGBA8888) {
			format = GL_RGBA; // OpenGL expects RGBA format for RGBA8888
		} else if (surface->format == SDL_PIXELFORMAT_ARGB8888) {
			format = GL_BGRA; // OpenGL expects BGRA format for ARGB8888
		}
		else {
			std::cerr << "Unsupported pixel format: " << surface->format << std::endl;
			SDL_DestroySurface(surface);
			std::exit(EXIT_FAILURE);
		}
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		// Set texture parameters
		glActiveTexture(GL_TEXTURE0);

	} else {
		std::cerr << "Failed to load texture or texture not found: " << filePath << std::endl;
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
	}
	SDL_DestroySurface(surface); // Clean up the surface
	return textureID; // Return the texture ID
}

void Object::TestTexture() {
	SDL_Window* win = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* bitmapTex = NULL;
	SDL_Surface* bitmapSurface = NULL;
	int width = 320, height = 240;
	bool loopShouldStop = false;

	SDL_Init(SDL_INIT_VIDEO);

	win = SDL_CreateWindow("Hello World", width, height, 0);

	renderer = SDL_CreateRenderer(win, NULL);

	bitmapSurface = SDL_LoadBMP("C:\\Users\\dnune\\OneDrive\\Documentos\\Visual Studio 2022\\Projects\\AugmentedReality\\images\\simprao_small.bmp");
	bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
	SDL_DestroySurface(bitmapSurface);

	while (!loopShouldStop)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_QUIT:
				loopShouldStop = true;
				break;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderTexture(renderer, bitmapTex, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(bitmapTex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);

	SDL_Quit();

	return;
}


bool Object::LoadFromOBJ(const std::string& filePath)
{
	tinyobj::ObjReader reader;
	if (!reader.ParseFromFile(filePath)) {
		std::cerr << "Erro ao carregar arquivo OBJ: " << filePath << std::endl;
		if (!reader.Error().empty()) std::cerr << "tinyobjloader: " << reader.Error() << std::endl;
		return false;
	}
	if (!reader.Warning().empty()) std::cout << "tinyobjloader: " << reader.Warning() << std::endl;

	const auto& attrib = reader.GetAttrib();
	const auto& shapes = reader.GetShapes();
	const auto& materials = reader.GetMaterials();

	vertices.clear();
	verticesTextureCoords.clear();
	indices.clear();

	for (const auto& shape : shapes) {
		for (const auto& idx : shape.mesh.indices) {
			// Indexes of the vertices
			indices.push_back(idx.vertex_index);
		}
	}
	vertices = attrib.GetVertices();
	verticesTextureCoords = attrib.texcoords;
	verticesSize = vertices.size();
	textureFilePath = materials[0].diffuse_texname;
	if (textureFilePath.empty()) {
		std::cerr << "No texture file specified in the OBJ file. Loading default color." << std::endl;
		// If no texture is specified, you can set a default color or handle it accordingly
		verticesColors.resize(verticesSize, 1.0f); // Default color white
		return false;
	}
	return true;
}
