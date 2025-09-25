```mermaid
classDiagram
    class "ConfigManager" {
        int windowWidth
        int windowHeight
        std::string runMode
        std::string opencvMode
        std::string VertexShaderFileName
        std::string FragmentShaderFileName
        glm::vec3 backgroundColor
        glm::vec3 cameraPosition
        glm::vec3 cameraViewDirection
        glm::vec3 cameraUpDirection
        float cameraFov
        float cameraNear
        float cameraFar
        float cameraAspectRatio
        float mouseSensitivity
        bool mouseMoveEnabled
        +ConfigManager()
        +ConfigManager(filename)
        +getString(key)
        +getInt(key)
        +getBool(key)
        +Load()
        +HasKey(key)
    }
    class "Colmap" {
        std::string database_path
        std::string image_path
        std::string output_path
        std::string output_type
        int max_image_size
        std::string workspace_path
        std::string workspace_format
        bool geom_consistency
        std::string input_type
        +Colmap()
        +LoadFromConfig(config)
        +RunCommandLine(config)
    }
    "Colmap" --> "ConfigManager" : usa