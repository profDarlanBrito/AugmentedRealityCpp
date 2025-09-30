cmake_minimum_required(VERSION 3.13)

# ---------------------------------------------------------------------------
# Geração automática do vcpkg.json
# ---------------------------------------------------------------------------

set(VCPKG_FINAL ${CMAKE_SOURCE_DIR}/vcpkg.json)

if(WIN32)
  message(STATUS "Gerando vcpkg.json para Windows...")
  file(WRITE ${VCPKG_FINAL} "{\n\"name\": \"argumentedreality\",\n\"version-string\": \"1.0.0\",\n\"dependencies\": [\n")
  file(APPEND ${VCPKG_FINAL} "    \"glm\",\n    \"tinyobjloader\",\n    \"yaml-cpp\",\n    \"sdl3\",\n    \"sdl3-image\",\n    \"sdl3-ttf\",\n    \"opencv\"\n")
  file(APPEND ${VCPKG_FINAL} "]\n}")
elseif(UNIX)
  message(STATUS "Gerando vcpkg.json para Linux...")
  file(WRITE ${VCPKG_FINAL} "{\n\"name\": \"argumentedreality\",\n\"version-string\": \"1.0.0\",\n\"dependencies\": [\n")
  file(APPEND ${VCPKG_FINAL} "    \"glm\",\n    \"tinyobjloader\",\n    \"yaml-cpp\"\n")
  file(APPEND ${VCPKG_FINAL} "]\n}")
endif()

# ---------------------------------------------------------------------------
# Configuração do projeto
# ---------------------------------------------------------------------------

message(STATUS "Compilando para o sistema operacional: ${CMAKE_SYSTEM_NAME}")

include(FetchContent)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(AugmentedReality)

# Diretório de saída do executável
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# ---------------------------------------------------------------------------
# Fontes do projeto
# ---------------------------------------------------------------------------

add_executable (AugmentedReality
        "src/AugmentedReality.cpp"
        "main.cpp"
        "src/Camera.cpp"
        "include/Camera.h"
        "src/ShaderOperations.cpp"
        "include/ShaderOperations.h"
        "src/Object.cpp"
        "include/GLMath.h"
        "src/GLMath.cpp"
        "src/glad.c"
        "src/ConfigManager.cpp"
        "src/OpenGLManipulations.cpp"
        "src/OpenCVManipulations.cpp"
        "src/Colmap.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.13)
  set_property(TARGET AugmentedReality PROPERTY CXX_STANDARD 20)
endif()
target_include_directories(AugmentedReality PRIVATE include)

# ---------------------------------------------------------------------------
# Dependências comuns (sempre via vcpkg)
# ---------------------------------------------------------------------------

find_package(glm CONFIG REQUIRED)
target_link_libraries(AugmentedReality PRIVATE glm::glm)

find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(AugmentedReality PRIVATE yaml-cpp::yaml-cpp)

find_package(tinyobjloader CONFIG REQUIRED)
target_link_libraries(AugmentedReality PRIVATE tinyobjloader::tinyobjloader)

# ---------------------------------------------------------------------------
# Dependências específicas por plataforma
# ---------------------------------------------------------------------------

if(WIN32)
  # Todas via vcpkg
  find_package(SDL3 CONFIG REQUIRED)
  target_link_libraries(AugmentedReality PRIVATE SDL3::SDL3)

  find_package(SDL3_image CONFIG REQUIRED)
  target_link_libraries(AugmentedReality PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)

  find_package(SDL3_ttf CONFIG REQUIRED)
  target_link_libraries(AugmentedReality PRIVATE $<IF:$<TARGET_EXISTS:SDL3_ttf::SDL3_ttf>,SDL3_ttf::SDL3_ttf,SDL3_ttf::SDL3_ttf-static>)

  find_package(OpenCV CONFIG REQUIRED)
  target_include_directories(AugmentedReality PRIVATE ${OpenCV_INCLUDE_DIRS})
  target_link_libraries(AugmentedReality PRIVATE ${OpenCV_LIBS})
elseif(UNIX)
  # OpenCV via sistema
  find_package(OpenCV REQUIRED)
  target_include_directories(AugmentedReality PRIVATE ${OpenCV_INCLUDE_DIRS})
  target_link_libraries(AugmentedReality PRIVATE ${OpenCV_LIBS})

  # SDL3 via sistema
  find_package(SDL3 REQUIRED)
  find_package(SDL3_image REQUIRED)
  find_package(SDL3_ttf REQUIRED)

  target_link_libraries(AugmentedReality PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)
endif()

