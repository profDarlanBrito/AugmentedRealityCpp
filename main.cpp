#include <iostream>
#include "AugmentedReality.h"
#include "ConfigManager.h"

using namespace std;

int main()
{
	// Initialize the Augmented Reality application
	AugmentedReality arApp;
    //arApp.object.TestTexture();
	arApp.object.LoadFromOBJ("../../../models/Plane_with_image.obj");
	ConfigManager cfg("../../../resources/config.yaml");
	arApp.cfg = cfg; // Load configuration from YAML file
	std::cout << arApp.cfg.testMode << std::endl;
    if (arApp.cfg.testMode == "OpenGL") {
        cout << "Initializing OpenGL ..." << endl;
        // Initialize SDL and OpenGL context
        if (!arApp.InitializeSDL()) {
            cerr << "Failed to initialize SDL!" << endl;
            return -1;
        }
        const std::vector<GLfloat> vertices = {
            -1.0f, -1.0f, 0.0f, // Bottom left
             1.0f, -1.0f, 0.0f, // Bottom right
             -1.0f,  1.0f, 0.0f,  // Top
             1.0f,  1.0f, 0.0f  // Top
        };
        const std::vector<GLfloat> verticesColors = {
            1.0f, 0.0f, 0.0f, // Bottom left color
            1.0f, 1.0f, 0.0f, // Bottom right color
            1.0f, 0.0f, 0.0f,  // Top color
            1.0f, 0.0f, 0.0f, // Bottom left color
        };

        const std::vector<GLuint> indices = {
            0, 1, 2, // First triangle
            1, 3, 2  // Second triangle
        };
        const std::vector<GLfloat> verticesNormals = {
            0.0f, 0.0f, 1.0f, // Normal for all vertices (assuming flat shading)
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f
		};
        const std::vector<GLfloat> verticesTextureCoords = {
            0.0f, 0.0f, // Bottom left texture coordinate
            1.0f, 0.0f, // Bottom right texture coordinate
            0.0f, 1.0f, // Top left texture coordinate
            1.0f, 1.0f  // Top right texture coordinate
		};

        arApp.GetOpenGLVersionInfo();
		arApp.SetWindowSize(arApp.cfg.windowWidth, arApp.cfg.windowHeight);
		arApp.camera.setPosition(arApp.cfg.cameraPosition);
		arApp.camera.mFov = arApp.cfg.cameraFov;
		arApp.camera.mNear = arApp.cfg.cameraNear;
		arApp.camera.mFar = arApp.cfg.cameraFar;
		arApp.camera.mAspectRatio = arApp.cfg.cameraAspectRatio;
        arApp.CreateGraphicsPipeline(arApp.cfg.VertexShaderFileName, arApp.cfg.FragmentShaderFileName);
        arApp.Run();
        return 0;
    }
	else {  
        std::cerr << "Invalid mode specified in config file. Expected 'OpenGL'." << std::endl;
        return -1;
    }

}
