cmake_minimum_required(VERSION 3.13)
project(AugmentedReality)

# ---------------------------------------------------------------------------
# Geração automática do vcpkg.json
# ---------------------------------------------------------------------------
set(VCPKG_FINAL "${CMAKE_SOURCE_DIR}/vcpkg.json")

if(WIN32)
  message(STATUS "Gerando vcpkg.json para Windows...")
  file(WRITE ${VCPKG_FINAL} "{\n\"name\": \"argumentedreality\",\n\"version-string\": \"1.0.0\",\n\"dependencies\": [\n")
  file(APPEND ${VCPKG_FINAL} "    \"glm\",\n")
  file(APPEND ${VCPKG_FINAL} "    \"tinyobjloader\",\n")
  file(APPEND ${VCPKG_FINAL} "    \"yaml-cpp\",\n")
  file(APPEND ${VCPKG_FINAL} "    \"sdl3\",\n")
  file(APPEND ${VCPKG_FINAL} "    \"sdl3-image\",\n")
  file(APPEND ${VCPKG_FINAL} "    \"sdl3-ttf\",\n")
  file(APPEND ${VCPKG_FINAL} "    \"opencv\",\n")
  file(APPEND ${VCPKG_FINAL} "    {\"name\": \"openmvg\", \"features\": [\"opencv\",\"openmp\",\"software\"]},\n")
  file(APPEND ${VCPKG_FINAL} "    {\"name\": \"openmvs\", \"features\": [\"ceres\",\"openmp\",\"cuda\"]}\n")
  file(APPEND ${VCPKG_FINAL} "]\n}")
elseif(UNIX)
  message(STATUS "Gerando vcpkg.json para Linux...")
  file(WRITE ${VCPKG_FINAL} "{\n\"name\": \"argumentedreality\",\n\"version-string\": \"1.0.0\",\n\"dependencies\": [\n")
  file(APPEND ${VCPKG_FINAL} "    \"glm\",\n")
  file(APPEND ${VCPKG_FINAL} "    \"tinyobjloader\",\n")
  file(APPEND ${VCPKG_FINAL} "    \"yaml-cpp\"\n")
  file(APPEND ${VCPKG_FINAL} "]\n}")
endif()

# ---------------------------------------------------------------------------
# Configurações gerais
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ---------------------------------------------------------------------------
# Fontes do projeto
# ---------------------------------------------------------------------------
add_executable(AugmentedReality
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

target_include_directories(AugmentedReality PRIVATE include)

# ---------------------------------------------------------------------------
# Dependências comuns via vcpkg
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
  # -----------------------------------------------------------------------
  # Windows usa tudo via vcpkg
  # -----------------------------------------------------------------------
  find_package(SDL3 CONFIG REQUIRED)
  find_package(SDL3_image CONFIG REQUIRED)
  find_package(SDL3_ttf CONFIG REQUIRED)
  find_package(OpenCV CONFIG REQUIRED)
  find_package(openmvg CONFIG REQUIRED)
  find_package(openmvs CONFIG REQUIRED)

  target_link_libraries(AugmentedReality PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)
  target_link_libraries(AugmentedReality PRIVATE ${OpenCV_LIBS} openmvg::openmvg openmvs::openmvs)

elseif(UNIX)
  # -----------------------------------------------------------------------
  # Linux usa libs manuais em /home/usuario/libs
  # -----------------------------------------------------------------------
  # CORREÇÃO DE PORTABILIDADE: Usando a variável de ambiente HOME
  set(LIBS_ROOT "$ENV{HOME}/libs")

  # -----------------------------------------------------------------------
  # SDL3 via sistema/instalação
  # -----------------------------------------------------------------------
  find_package(SDL3 REQUIRED)
  find_package(SDL3_image REQUIRED)
  find_package(SDL3_ttf REQUIRED)
  target_link_libraries(AugmentedReality PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)


  # -----------------------------------------------------------------------
  # OpenCV via sistema
  # -----------------------------------------------------------------------
  find_package(OpenCV REQUIRED)
  target_include_directories(AugmentedReality PRIVATE ${OpenCV_INCLUDE_DIRS})
  target_link_libraries(AugmentedReality PRIVATE ${OpenCV_LIBS})

  # -----------------------------------------------------------------------
  # OpenMVG/OpenMVS manual (Manutenção dos caminhos explícitos corrigidos)
  # -----------------------------------------------------------------------
  set(OPENMVG_ROOT "${LIBS_ROOT}/openMVG")
  set(OPENMVS_ROOT "${LIBS_ROOT}/openMVS")

  target_include_directories(AugmentedReality PRIVATE
          "${OPENMVG_ROOT}/src"
          "${OPENMVS_ROOT}/libs"
  )

  # Detecta tipo de build (Release/Debug)
  if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release")
  endif()
  string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWER)

  # Caminho da OpenMVG
  set(OPENMVG_BUILD_DIR "${OPENMVG_ROOT}/build/Linux-x86_64-Release")

  # Caminho da OpenMVS
  set(OPENMVS_BUILD_DIR "${OPENMVS_ROOT}/build/lib")

  set(OPENMVG_LIBS
          # OpenMVG: 'common' substituído por 'numeric'
          "${OPENMVG_BUILD_DIR}/libopenMVG_numeric.a"
          "${OPENMVG_BUILD_DIR}/libopenMVG_features.a"
          "${OPENMVG_BUILD_DIR}/libopenMVG_sfm.a"
          "${OPENMVG_BUILD_DIR}/libopenMVG_multiview.a"
          "${OPENMVG_BUILD_DIR}/libopenMVG_system.a"
  )

  set(OPENMVS_LIBS
          # OpenMVS: Corrigido o nome de 'libOpenMVS.a' para 'libMVS.a' e adicionado as dependências
          "${OPENMVS_BUILD_DIR}/libMVS.a"
          "${OPENMVS_BUILD_DIR}/libCommon.a"
          "${OPENMVS_BUILD_DIR}/libIO.a"
          "${OPENMVS_BUILD_DIR}/libMath.a"
  )

  # Verifica se todas as libs OPENMVG/OPENMVS existem
  foreach(lib ${OPENMVG_LIBS} ${OPENMVS_LIBS})
    if(NOT EXISTS ${lib})
      # O $ENV{HOME} garantirá que o caminho exibido seja o correto para o usuário atual
      message(FATAL_ERROR "Biblioteca não encontrada: ${lib}")
    endif()
  endforeach()

  # Linka apenas as libs OpenMVG/OpenMVS manualmente
  target_link_libraries(AugmentedReality PRIVATE ${OPENMVG_LIBS} ${OPENMVS_LIBS})
endif()
