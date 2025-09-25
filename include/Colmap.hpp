#pragma once
#include <string>
#include <iostream>
#include <ConfigManager.h>
//#ifdef _WIN32
//#include <windows.h>
//#else
//#include <unistd.h>
//#endif

class Colmap {
public:
    // Campos de configuração
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

    // Carrega os campos do ConfigManager
    void LoadFromConfig(const ConfigManager& config);

    bool IsColmapInPath() const;

    // Executa o pipeline COLMAP via linha de comando (PowerShell)
    void RunCommandLine(const ConfigManager& config);
};