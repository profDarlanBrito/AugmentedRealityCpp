#pragma once
#include <string>
#include <iostream>
#include <ConfigManager.h>
#include <fstream>
#include <sstream>

class Colmap {
public:
	// Configuration parameters
    std::string database_path;
    std::string image_path;
    std::string output_path;
    std::string output_type;
    int max_image_size;
    std::string workspace_path;
    std::string workspace_format;
    bool geom_consistency;
    std::string input_type;

    Colmap() = default;

	// Load configuration from ConfigManager
    void LoadFromConfig(const ConfigManager& config);

    bool IsColmapInPath() const;

    // Run the pipeline for COLMAP using command line (PowerShell)
    void RunCommandLine(const ConfigManager& config);

    std::string GetColmapCommand(const ConfigManager& config, const std::string Key) const;
};