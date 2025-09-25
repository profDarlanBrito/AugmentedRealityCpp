#include "Colmap.hpp"

void Colmap::LoadFromConfig(const ConfigManager& config) {
    database_path    = config.getString("colmap_database_path");
    image_path       = config.getString("colmap_image_path");
    output_path      = config.getString("colmap_output_path");
    output_type      = config.getString("colmap_output_type");
    //max_image_size   = config.getInt("max_image_size");
    workspace_path   = config.getString("colmap_workspace_path");
    workspace_format = config.getString("colmap_workspace_format");
    geom_consistency = config.getBool("colmap_geometry_consistency_check");
    input_type       = config.getString("colmap_input_type");
}

bool Colmap::IsColmapInPath() const {
#ifdef _WIN32
    // In the Windows, try to locate the executable of the colmap using 'where'.
    if (std::system("where colmap >nul 2>nul") == 0) {
        return true;
    }
#else
    // In the Linux, try to locate the executable of the colmap using 'which'
    if (std::system("which colmap >/dev/null 2>&1") == 0) {
        return true;
    }
#endif
    return false;
}
void Colmap::RunCommandLine(const ConfigManager& config) {
    LoadFromConfig(config);
	std::string colmapPath = "colmap"; // Assumindo que 'colmap' está no PATH do sistema
    if (!IsColmapInPath()) {
        std::cerr << "Error: 'colmap' command not found in PATH. Please ensure COLMAP is installed and added to your system PATH or configure the path in the Config.yaml file" << std::endl;
		colmapPath = config.getString("colmap_executable_path");
	}
    std::string cmd;

    // Todas as imagens usam os mesmos parâmetros intrínsecos
    std::string intrinsics = "--ImageReader.single_camera 1";

    // 1. feature_extractor
    cmd = colmapPath + " feature_extractor --database_path \"" + database_path +
          "\" --image_path \"" + image_path + "\" " + intrinsics;
    std::cout << cmd << std::endl;
    std::system(cmd.c_str());

    // 2. exhaustive_matcher
    cmd = colmapPath + " exhaustive_matcher --database_path \"" + database_path + "\"";
    std::cout << cmd << std::endl;
    std::system(cmd.c_str());

    // 3. mkdir para pasta sparse
    cmd = "mkdir \"" + output_path + "/sparse\"";
    std::cout << cmd << std::endl;
    std::system(cmd.c_str());

    // 4. mapper
    cmd = colmapPath + " mapper --database_path \"" + database_path +
          "\" --image_path \"" + image_path +
          "\" --output_path \"" + output_path + "/sparse\"";
    std::cout << cmd << std::endl;
    std::system(cmd.c_str());

    // 5. image_undistorter
    cmd = colmapPath + " image_undistorter --image_path \"" + image_path +
          "\" --input_path \"" + output_path + "/sparse/0\""
          " --output_path \"" + output_path + "/dense\""
          " --output_type " + output_type;
    std::cout << cmd << std::endl;
    std::system(cmd.c_str());

    // 6. patch_match_stereo
    cmd = colmapPath + " patch_match_stereo --workspace_path \"" + output_path + "/dense\""
          " --workspace_format " + workspace_format +
          " --PatchMatchStereo.geom_consistency " + (geom_consistency ? "true" : "false");
    std::cout << cmd << std::endl;
    std::system(cmd.c_str());

    // 7. stereo_fusion
    cmd = colmapPath + " stereo_fusion --workspace_path \"" + output_path + "/dense\""
          " --workspace_format " + workspace_format +
          " --input_type " + input_type +
          " --output_path \"" + output_path + "/dense/fused.ply\"";
    std::cout << cmd << std::endl;
    std::system(cmd.c_str());

    // 8. poisson_mesher
    cmd = colmapPath + " poisson_mesher --input_path \"" + output_path + "/dense/fused.ply\""
          " --output_path \"" + output_path + "/dense/meshed-poisson.ply\"";
    std::cout << cmd << std::endl;
    std::system(cmd.c_str());

    // 9. delaunay_mesher
    cmd = colmapPath + " delaunay_mesher --input_path \"" + output_path + "/dense\""
          " --output_path \"" + output_path + "/dense/meshed-delaunay.ply\"";
    std::cout << cmd << std::endl;
    std::system(cmd.c_str());
}