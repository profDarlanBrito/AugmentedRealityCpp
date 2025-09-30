#!/bin/bash
# systemLinuxDependencies.sh
# Script para instalar OpenCV e SDL3 nativos com suporte a FFMPEG no Ubuntu

set -e  # Para o script parar se algum comando falhar

echo "Atualizando lista de pacotes..."
sudo apt update

echo "Instalando dependências do FFMPEG para OpenCV..."
sudo apt install -y ffmpeg libavcodec-dev libavformat-dev libavutil-dev libswscale-dev libavresample-dev

echo "Instalando SDL3 e módulos necessários..."
sudo apt install -y libsdl3-2.0-0 libsdl3-dev \
                    libsdl3-image-2.0-0 libsdl3-image-dev \
                    libsdl3-ttf-2.0-0 libsdl3-ttf-dev

echo "Instalando OpenCV nativo com suporte a vídeo (FFMPEG)..."
sudo apt install -y libopencv-dev libopencv-videoio-dev \
                    libopencv-core-dev libopencv-imgcodecs-dev \
                    libopencv-highgui-dev

echo "Dependências nativas para OpenCV (com FFMPEG) e SDL3 instaladas com sucesso!"
