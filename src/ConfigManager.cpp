#include "ConfigManager.h"
#include <stdexcept>
using namespace YAML;


/**
* @brief ConfigManager constructor that initializes default values.
*/
ConfigManager::ConfigManager() {
    // Default constructor initializes with default values
    windowWidth = 800;
    windowHeight = 600;
    runMode = "OpenGL";
    VertexShaderFileName = "../../../shaders/vertex_shader.glsl";
    FragmentShaderFileName = "../../../shaders/fragment_shader.glsl";
    cameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
    cameraFov = 45.0f;
    cameraNear = 0.1f;
    cameraFar = 100.0f;
    cameraAspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    backgroundColor = glm::vec3(0.3f, 0.3f, 0.3f);
	mouseMoveEnabled = true;
	mouseSensitivity = 0.1f; // Default mouse sensitivity
}
/**
* @brief ConfigManager constructor that loads configuration from a YAML file.
* @param filename The path to the YAML configuration file.
* @throws std::runtime_error if the file cannot be loaded or parsed.
*/
ConfigManager::ConfigManager(const std::string& filename) {
    try {
        config = YAML::LoadFile(filename);
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Erro ao carregar arquivo de configuração: ") + e.what());
    }
    windowWidth = 800;
    windowHeight = 600;
    runMode = "OpenGL";
    VertexShaderFileName = "../../../shaders/vertex_shader.glsl";
    FragmentShaderFileName = "../../../shaders/fragment_shader.glsl";
	Load();
}

/**
* @brief Loads configuration values from the YAML file.
* @note This function checks for the existence of each key and retrieves its value.
* @note If add a key in the YAML file, it should be added here to ensure it is loaded correctly.
* @note If you add a new key to the YAML file be sure to change the operator= function to copy the new key from another ConfigManager object.
* @return true if all keys were found and loaded successfully, false otherwise.
*/
bool ConfigManager::Load() {
	bool success = true;
    if (HasKey("window_width")) {
        windowWidth = Get<int>("window_width");
        std::cout << "Largura da janela: " << windowWidth << std::endl;
    }
    else {
		std::cerr << "Key 'window_width' not found in the configuration file." << std::endl;
		success = false;
    }
    if(HasKey("window_height")) {
        windowHeight = Get<int>("window_height");
        std::cout << "Altura da janela: " << windowHeight << std::endl;
    }
    else {
		std::cerr << "Key 'window_height' not found in the configuration file." << std::endl;
        success = false;
    }
    if (HasKey("run_mode")) {
        runMode = Get<std::string>("run_mode");
        std::cout << "Modo de teste: " << runMode << std::endl;
    } else {
        std::cerr << "Key 'run_mode' not found in the configuration file." << std::endl;
        success = false;
    }
    if (HasKey("vertex_Shader_file")) {
        VertexShaderFileName = Get<std::string>("vertex_Shader_file");
        std::cout << "Arquivo do shader de vértices: " << VertexShaderFileName << std::endl;
    } else {
        std::cerr << "Key 'Vertex Shader file' not found in the configuration file." << std::endl;
        success = false;
    }
    if (HasKey("fragment_Shader_file")) {
        FragmentShaderFileName = Get<std::string>("fragment_Shader_file");
        std::cout << "Arquivo do shader de fragmentos: " << FragmentShaderFileName << std::endl;
    } else {
        std::cerr << "Key 'Fragment Shader file' not found in the configuration file." << std::endl;
        success = false;
    }
    if (HasKey("camera_position")) {
        auto cameraPos = Get<std::vector<float>>("camera_position");
        if (cameraPos.size() == 3) {
            cameraPosition = glm::vec3(cameraPos[0], cameraPos[1], cameraPos[2]);
            std::cout << "Posição da câmera: " << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << std::endl;
        } else {
            std::cerr << "Invalid 'camera_position' format in the configuration file." << std::endl;
            success = false;
        }
    } else {
        std::cerr << "Key 'camera_position' not found in the configuration file." << std::endl;
        success = false;
	}

    if (HasKey("camera_view_direction")) {
        auto cameraViewDir = Get<std::vector<float>>("camera_view_direction");
        if (cameraViewDir.size() == 3) {
            cameraViewDirection = glm::vec3(cameraViewDir[0], cameraViewDir[1], cameraViewDir[2]);
            std::cout << "Direção de visão da câmera: " << cameraViewDirection.x << ", " << cameraViewDirection.y << ", " << cameraViewDirection.z << std::endl;
        } else {
            std::cerr << "Invalid 'camera_view_direction' format in the configuration file." << std::endl;
            success = false;
        }
    }
    else {
        std::cerr << "Key 'camera_view_direction' not found in the configuration file." << std::endl;
        success = false;
    }
    if (HasKey("camera_up_direction")) {
        auto cameraUpDir = Get<std::vector<float>>("camera_up_direction");
        if (cameraUpDir.size() == 3) {
            cameraUpDirection = glm::vec3(cameraUpDir[0], cameraUpDir[1], cameraUpDir[2]);
            std::cout << "Direção para cima da câmera: " << cameraUpDirection.x << ", " << cameraUpDirection.y << ", " << cameraUpDirection.z << std::endl;
        } else {
            std::cerr << "Invalid 'camera_up_direction' format in the configuration file." << std::endl;
            success = false;
        }
    }
    else {
        std::cerr << "Key 'camera_up_direction' not found in the configuration file." << std::endl;
        success = false;
    }
    if (HasKey("background_color")) {
        auto bgColor = Get<std::vector<float>>("background_color");
        if (bgColor.size() == 3) {
            backgroundColor = glm::vec3(bgColor[0], bgColor[1], bgColor[2]);
            std::cout << "Cor de fundo: " << backgroundColor.x << ", " << backgroundColor.y << ", " << backgroundColor.z << std::endl;
        } else {
            std::cerr << "Invalid 'background_color' format in the configuration file." << std::endl;
            success = false;
        }
    } else {
        std::cerr << "Key 'background_color' not found in the configuration file." << std::endl;
        success = false;
	}
    if (HasKey("camera_fov")) {
        cameraFov = Get<float>("camera_fov");
        if (cameraFov > 0.0f && cameraFov < 180.0f) {
            std::cout << "Campo de visão da câmera: " << cameraFov << std::endl;
        } else {
            std::cerr << "Invalid 'camera_fov' value in the configuration file." << std::endl;
            success = false;
        }
    } else {
        std::cerr << "Key 'camera fov' not found in the configuration file." << std::endl;
        success = false;
	}
    if (HasKey("camera_near_plane")) {
        cameraNear = Get<float>("camera_near_plane");
        if (cameraNear > 0.0f) {
            std::cout << "Distância próxima da câmera: " << cameraNear << std::endl;
        } else {
            std::cerr << "Invalid 'Camera near plane' value in the configuration file." << std::endl;
            success = false;
        }
    } else {
        std::cerr << "Key 'camera near plane' not found in the configuration file." << std::endl;
        success = false;
    }
    if (HasKey("camera_far_plane")) {
        cameraFar = Get<float>("camera_far_plane");
        if (cameraFar > 0.0f) {
            std::cout << "Distância distante da câmera: " << cameraFar << std::endl;
        } else {
            std::cerr << "Invalid 'camera far plane' value in the configuration file." << std::endl;
            success = false;
        }
    } else {
        std::cerr << "Key 'camera far plane' not found in the configuration file." << std::endl;
        success = false;
	}
    if (HasKey("camera_aspect_ratio")) {
        cameraAspectRatio = Get<float>("camera_aspect_ratio");
        if (cameraAspectRatio > 0.0f) {
            std::cout << "Proporção da câmera: " << cameraAspectRatio << std::endl;
        } else {
			cameraAspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
			std::cout << "Proporção da câmera não especificada, usando proporção da janela: " << cameraAspectRatio << std::endl;
        }
    } else {
        std::cerr << "Key 'camera aspect ratio' not found in the configuration file." << std::endl;
        success = false;
    }
    if (HasKey("mouse_sensitivity")) {
        mouseSensitivity = Get<float>("mouse_sensitivity");
        if (mouseSensitivity > 0.0f) {
            std::cout << "Sensibilidade do mouse: " << mouseSensitivity << std::endl;
        } else {
            std::cerr << "Invalid 'mouse_sensitivity' value in the configuration file." << std::endl;
            success = false;
        }
    } else {
        std::cerr << "Key 'mouse sensitivity' not found in the configuration file." << std::endl;
        success = false;
	}
    if (!success) {
        std::cerr << "Some configuration values were not loaded successfully." << std::endl;
	}
    if (HasKey("mouse_move_enabled")) {
        mouseMoveEnabled = Get<bool>("mouse_move_enabled");
        std::cout << "Mouse movement enabled: " << (mouseMoveEnabled ? "true" : "false") << std::endl;
    } else {
        std::cerr << "Key 'mousemove_enabled' not found in the configuration file." << std::endl;
        success = false;
	}
	return success;
}

/**
* @brief Assignment operator for ConfigManager.
* @param other The ConfigManager object to copy from.
* @return A reference to the current ConfigManager object.
* @note This operator allows for copying the configuration values from another ConfigManager object.
*/
ConfigManager& ConfigManager::operator=(const ConfigManager& other)
{
    if (this != &other) {
        windowWidth = other.windowWidth;
        windowHeight = other.windowHeight;
        runMode = other.runMode;
        VertexShaderFileName = other.VertexShaderFileName;
        FragmentShaderFileName = other.FragmentShaderFileName;
        cameraPosition = other.cameraPosition;
        cameraFov = other.cameraFov;
        cameraNear = other.cameraNear;
        cameraFar = other.cameraFar;
        cameraAspectRatio = other.cameraAspectRatio;
        backgroundColor = other.backgroundColor;
		mouseMoveEnabled = other.mouseMoveEnabled;
		mouseSensitivity = other.mouseSensitivity;
        cameraViewDirection = other.cameraViewDirection;
	    cameraUpDirection = other.cameraUpDirection;
    }
    return *this;
}