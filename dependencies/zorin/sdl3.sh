#!/bin/bash
# installSDL3Nativo_Final.sh
set -e

sudo apt update

# Instalando a lista completa de dependências recomendadas pela Wiki do SDL3
sudo apt install -y build-essential git make cmake pkg-config \
    libasound2-dev \
    libpulse-dev \
    libaudio-dev \
    libjack-dev \
    libpipewire-0.3-dev \
    libsndio-dev \
    libx11-dev \
    libxext-dev \
    libxrandr-dev \
    libxcursor-dev \
    libxfixes-dev \
    libxi-dev \
    libxss-dev \
    libxkbcommon-dev \
    libdrm-dev \
    libgbm-dev \
    libgl1-mesa-dev \
    libgles2-mesa-dev \
    libegl1-mesa-dev \
    libdbus-1-dev \
    libibus-1.0-dev \
    libudev-dev \
    libwayland-dev \
    wayland-protocols \
    libdecor-0-dev \
    libavcodec-dev \
    libavformat-dev \
    libavutil-dev \
    libswscale-dev \
    libswresample-dev \
    libfreetype-dev \
    libharfbuzz-dev

TEMP_DIR=$(mktemp -d)
cd $TEMP_DIR

compile_sdl() {
    local repo=$1
    local name=$2
    echo "--- Baixando e compilando $name ---"
    git clone "https://github.com/libsdl-org/$repo.git" --depth 1
    cmake -S "$repo" -B "build_$repo" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local
    cmake --build "build_$repo" -j$(nproc)
    sudo cmake --install "build_$repo"
}

# Executar builds
compile_sdl "SDL" "SDL3 Core"
compile_sdl "SDL_image" "SDL3 Image"
compile_sdl "SDL_ttf" "SDL3 TTF"

echo "Atualizando ldconfig..."
sudo ldconfig

echo "-------------------------------------------------------"
echo "SDL3, SDL3_image e SDL3_ttf instalados com sucesso!"
echo "-------------------------------------------------------"

cd ~
rm -rf $TEMP_DIR