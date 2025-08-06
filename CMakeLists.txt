# CMakeList.txt: projeto de CMake para TesteCMake, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.13)

message(STATUS "Compilando para o sistema operacional: ${CMAKE_SYSTEM_NAME}")

include(FetchContent)

# Habilite a Recarga Dinâmica para compiladores MSVC, se houver suporte.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("AugmentedReality")


# Adicione a origem ao executável deste projeto.
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
                "src/OpenGLManipulations.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.13)
  set_property(TARGET AugmentedReality PROPERTY CXX_STANDARD 20)
endif()
target_include_directories(AugmentedReality PRIVATE include)

find_package(glm CONFIG REQUIRED)
target_link_libraries(AugmentedReality PRIVATE glm::glm)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(AugmentedReality PRIVATE SDL3::SDL3)

find_package(SDL3_image CONFIG REQUIRED)
target_link_libraries(AugmentedReality PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)

find_package(SDL3_ttf CONFIG REQUIRED)
target_link_libraries(AugmentedReality PRIVATE $<IF:$<TARGET_EXISTS:SDL3_ttf::SDL3_ttf>,SDL3_ttf::SDL3_ttf,SDL3_ttf::SDL3_ttf-static>)

find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(AugmentedReality PRIVATE yaml-cpp::yaml-cpp)

find_package(tinyobjloader CONFIG REQUIRED)
target_link_libraries(AugmentedReality PRIVATE tinyobjloader::tinyobjloader)

find_package(OpenCV CONFIG REQUIRED)
target_include_directories(AugmentedReality PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(AugmentedReality PRIVATE ${OpenCV_LIBS})

