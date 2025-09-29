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

void OpenCVManipulations::Run(std::string option) {
	OpenCVManipulations opcvm;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "******************************************************************" << std::endl;
	std::cout << "OpenCV Manipulations." << std::endl;
	std::cout << "******************************************************************" << std::endl;
	std::cout << "\n\n\n\n" << std::endl;
	if (strcmp(option.c_str(), "test") == 0) {
		opcvm.MainTests();
	}
	else if (strcmp(option.c_str(), "framing") == 0) {
		opcvm.SaveVideoFrames("../../../videos/Clio.mp4",
			"../../../videos/frames");
	}
	else {
		std::cerr << "Invalid option. Use 'test' or 'framing'." << std::endl;
	}
}

void OpenCVManipulations::SaveVideoFrames(const std::string& videoPath, const std::string& outputDir) {
	std::cout << "************************************************" << std::endl;
	std::cout << " Starting framing the video " << std::endl;
	std::cout << "************************************************" << std::endl;
    cv::VideoCapture cap(videoPath);
	double fps = GetVideoFrameRate(cap);
    if (!cap.isOpened()) {
        std::cerr << "Not possible to open the video file: " << videoPath << std::endl;
        return;
    }

    // Extrai o nome base do arquivo de v�deo (sem caminho e extens�o)
    size_t lastSlash = videoPath.find_last_of("/\\");
    std::string filename = (lastSlash == std::string::npos) ? videoPath : videoPath.substr(lastSlash + 1);
    size_t lastDot = filename.find_last_of('.');
    std::string baseName = (lastDot == std::string::npos) ? filename : filename.substr(0, lastDot);

    int frameNumber = 1;
	int contFrame = 0;
    cv::Mat frame;
    while (cap.read(frame)) {
		if (contFrame % 2 == 0) { // Salva apenas a cada 10 quadros
			char buffer[256];
			snprintf(buffer, sizeof(buffer), "%s/%s_%03d.png", outputDir.c_str(), baseName.c_str(), frameNumber);
			cv::imwrite(buffer, frame);
			frameNumber++;
			std::cout << "*";
		}
		contFrame++;
    }
	std::cout << "************************************************" << std::endl;
	std::cout << " Frames save in: " << outputDir << std::endl;
	std::cout << " Ending framing the video " << std::endl;
	std::cout << "************************************************" << std::endl;
}

void OpenCVManipulations::SaveVideoFrames(const std::string& videoPath, const std::string& outputDir, const double desiredFps) {
	std::cout << "************************************************" << std::endl;
	std::cout << " Starting framing the video " << std::endl;
	std::cout << "************************************************" << std::endl;
	cv::VideoCapture cap(videoPath);
	double fps = GetVideoFrameRate(cap);
	if (!cap.isOpened()) {
		std::cerr << "Not possible to open the video file: " << videoPath << std::endl;
		return;
	}

	// Extrai o nome base do arquivo de v�deo (sem caminho e extens�o)
	size_t lastSlash = videoPath.find_last_of("/\\");
	std::string filename = (lastSlash == std::string::npos) ? videoPath : videoPath.substr(lastSlash + 1);
	size_t lastDot = filename.find_last_of('.');
	std::string baseName = (lastDot == std::string::npos) ? filename : filename.substr(0, lastDot);

	int frameNumber = 1;
	int contFrame = 0;
	cv::Mat frame;
	int rate = static_cast<int>(fps / desiredFps);
	while (cap.read(frame)) {
		if (contFrame % rate == 0) { // Salva apenas a cada 10 quadros
			char buffer[256];
			snprintf(buffer, sizeof(buffer), "%s/%s_%03d.png", outputDir.c_str(), baseName.c_str(), frameNumber);
			cv::imwrite(buffer, frame);
			frameNumber++;
			std::cout << "*";
		}
		contFrame++;
	}
	std::cout << "************************************************" << std::endl;
	std::cout << " Frames save in: " << outputDir << std::endl;
	std::cout << " Ending framing the video " << std::endl;
	std::cout << "************************************************" << std::endl;
}

double OpenCVManipulations::GetVideoFrameRate(const std::string& videoPath) {
    cv::VideoCapture cap(videoPath);
    if (!cap.isOpened()) {
        std::cerr << "It's not possible to opend the video in file: " << videoPath << std::endl;
        return 0.0;
    }
    // CV_CAP_PROP_FPS ou cv::CAP_PROP_FPS retorna a taxa de quadros
    double fps = cap.get(cv::CAP_PROP_FPS);
    return fps;
}

double OpenCVManipulations::GetVideoFrameRate(const cv::VideoCapture& cap) {
	// CV_CAP_PROP_FPS ou cv::CAP_PROP_FPS retorna a taxa de quadros
	double fps = cap.get(cv::CAP_PROP_FPS);
	return fps;
}