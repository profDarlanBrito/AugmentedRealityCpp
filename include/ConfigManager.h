#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP
#include <string>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <glm/glm.hpp>

#ifndef CONFIG_FILE_PATH_NAME
#define CONFIG_FILE_PATH_NAME "../../../resources/config.yaml"
#endif // !CONFIG_FILE_PATH_NAME

class ConfigManager {
public:
	int windowWidth;
	int windowHeight;
	std::string runMode;
	std::string VertexShaderFileName;
	std::string FragmentShaderFileName;
	glm::vec3 backgroundColor;

	// Camera parameters
	glm::vec3 cameraPosition;
	glm::vec3 cameraViewDirection;
	glm::vec3 cameraUpDirection;

    float cameraFov;
	float cameraNear;
	float cameraFar;
	float cameraAspectRatio;
    float mouseSensitivity;
	bool mouseMoveEnabled;


    ConfigManager();

    explicit ConfigManager(const std::string& filename);

    template<typename T>
    T Get(const std::string& key) const {
        return config[key].as<T>();
    }

    bool HasKey(const std::string& key) const {
        return config[key] && config[key].IsDefined();
    }

    bool Load();
	ConfigManager& operator=(const ConfigManager& other);
private:
    YAML::Node config;
};
#endif // CONFIGMANAGER_HPP