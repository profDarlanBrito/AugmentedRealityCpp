#!/bin/bash
# systemDependencies.sh
# Script para instalar OpenCV e SDL3 nativos com suporte a FFMPEG no Ubuntu

set -e  # Para o script parar se algum comando falhar

echo "Atualizando lista de pacotes..."
sudo apt update

echo "Instalando dependências do FFMPEG para OpenCV..."
sudo apt-get install -y libavcodec-dev libavformat-dev libswscale-dev libavutil-dev libswresample-dev

echo "Instalando SDL3 e módulos necessários..."
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev

echo "Instalando OpenCV nativo com suporte a vídeo (FFMPEG)..."
sudo apt install -y libopencv-dev libopencv-videoio-dev \
                    libopencv-core-dev libopencv-imgcodecs-dev \
                    libopencv-highgui-dev

echo "Dependências nativas para OpenCV (com FFMPEG) e SDL3 instaladas com sucesso!"
