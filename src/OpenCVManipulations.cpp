#include <opencv2/opencv.hpp>
#include <iostream>
#include "OpenCVManipulations.hpp"

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
}

void OpenCVManipulations::Run() {
	std::cout << "Running OpenCV Manipulations..." << std::endl;
	MainTests();
	std::cout << "OpenCV Manipulations completed." << std::endl;
}