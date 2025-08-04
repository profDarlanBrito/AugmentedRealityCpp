#include <iostream>
#include "AugmentedReality.h"
#include "ConfigManager.h"
#include "OpenCVManipulations.hpp"
#include "OpenGLManipulations.hpp"

using namespace std;
/**
* @brief Main function to run the Augmented Reality application.
* @note This function initializes the Augmented Reality application, loads the configuration from a YAML file, and starts the OpenGL rendering loop if the test mode is set to "OpenGL".
* @see AugmentedReality
* @see IMPORTANT: AFTER COMPILING THE CODE FIRST TIME VERIFY IF CMAKEFILE HAS COMMANDS DESCRIBED IN THE OUTPUT WINDOW.
* @return 0 if the application runs successfully, -1 if there is an error in initialization or configuration.
*/
int main()
{
	// Initialize the Augmented Reality application
	AugmentedReality arApp;
    //arApp.object.TestTexture();
	arApp.object.LoadFromOBJ("../../../models/Cubo.obj");
	ConfigManager cfg("../../../resources/config.yaml");
	arApp.cfg = cfg; // Load configuration from YAML file
	std::cout << arApp.cfg.runMode << std::endl;
    if (arApp.cfg.runMode == "AugmentedReality") {
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
    else if (arApp.cfg.runMode == "OpenCV") {
		OpenCVManipulations::Run();
        return 0;
	}
    else if (cfg.runMode == "OpenGL") {
		OpenGLManipulations::Run();
    }
	else {  
        std::cerr << "Invalid mode specified in config file. Expected 'OpenGL'." << std::endl;
        return -1;
    }

}
