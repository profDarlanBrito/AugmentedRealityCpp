#ifndef OPENCVMANIPULATIONS_HPP
#define OPENCVMANIPULATIONS_HPP
#include <opencv2/opencv.hpp>
#include <iostream>
/**
 * @brief Main function to run OpenCV tests.
 * 
 * This function loads an image from a file, displays it in a window, and waits for a key press before closing the window.
 * 
 * @note Ensure that the image path is correct relative to the executable or working directory.
 */
class OpenCVManipulations {
public:
	static void MainTests();
	static void cameraMatrixManipulations();
	static void Run();
};
#endif // OPENCVMANIPULATIONS_HPP