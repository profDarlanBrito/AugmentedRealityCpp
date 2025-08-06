#define GLM_ENABLE_EXPERIMENTAL // Enable experimental features in GLM

#include <opencv2/opencv.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp> // Required for glm::to_string
#include "OpenCVManipulations.hpp"
#include "AugmentedReality.h"
#include "ShaderOperations.h"
#include "ConfigManager.h"


/**
 * @brief Main function to run OpenCV tests.
 * 
 * This function loads an image from a file, displays it in a window, and waits for a key press before closing the window.
 * 
 * @note Ensure that the image path is correct relative to the executable or working directory.
 */

void OpenCVManipulations::MainTests() {
	// Load an image from file
	cv::Mat image = cv::imread("../../../images/simprao.jpg");
	if (image.empty()) {
		std::cerr << "Could not open or find the image!" << std::endl;
		return;
	}
	// Display the image in a window
	cv::imshow("Sample Image", image);
	
	// Wait for a key press indefinitely
	cv::waitKey(1000.0f);
	
	// Destroy all windows
	cv::destroyAllWindows();
}

void OpenCVManipulations::cameraMatrixManipulations()
{
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	glm::vec4 X = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec4 x = cameraMatrix * X;
	std::cout << "x: " << glm::to_string(x) << std::endl;
}

void OpenCVManipulations::Run() {
	std::cout << "OpenCV Manipulations completed." << std::endl;
}