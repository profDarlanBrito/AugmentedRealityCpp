#include <iostream>
#include "AugmentedReality.h"
#include "ConfigManager.h"
#include "OpenCVManipulations.hpp"
#include "OpenGLManipulations.hpp"
#include <Colmap.hpp>

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

	ConfigManager cfg("../resources/config.yaml");

    if (cfg.runMode == "OpenCV") {
		OpenCVManipulations::Run(cfg.opencvMode);
        return 0;
	}
    if (cfg.runMode == "OpenGL") {
		OpenGLManipulations::Run();
    }
    if (cfg.runMode == "COLMAP") {
        Colmap colmap;
        if(cfg.opencvMode == "framing") {
            OpenCVManipulations opcvm;
            opcvm.SaveVideoFrames(cfg.getString("video_path"), cfg.getString("video_frames_output_path"), cfg.getInt("frame_rate"));
		}
        colmap.RunCommandLine(cfg);
        return 0;
	}
	else {  
        std::cerr << "Invalid mode specified in config file. Expected 'OpenGL'." << std::endl;
        return -1;
    }

}
