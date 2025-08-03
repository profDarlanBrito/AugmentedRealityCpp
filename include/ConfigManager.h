#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP
#include <string>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <glm/glm.hpp>

class ConfigManager {
public:
	int windowWidth;
	int windowHeight;
	std::string testMode;
	std::string VertexShaderFileName;
	std::string FragmentShaderFileName;
	glm::vec3 cameraPosition;
    float cameraFov;
	float cameraNear;
	float cameraFar;
	float cameraAspectRatio;
	glm::vec3 backgroundColor;


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