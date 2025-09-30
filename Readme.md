# Projeto AugmentedRealityCpp

Este projeto é uma aplicação de Realidade Aumentada desenvolvida em C++ que utiliza OpenGL para renderização 3D e SDL3 para gerenciamento de janelas e eventos. [cite\_start]Ele também possui funcionalidades para manipulação de câmeras e objetos 3D, e integra bibliotecas como OpenCV para manipulações de imagem e GLM para matemática de vetores e matrizes[cite: 5].

## Sobre o Projeto

A aplicação é configurável através de um arquivo YAML (`config.yaml`) e pode operar em diferentes modos, como "OpenGL" e "OpenCV"[cite: 1].

As principais funcionalidades incluem:

  * **Renderização 3D**: Utiliza OpenGL 3.1 com um pipeline de renderização configurado para desenhar objetos 3D[cite: 5].
  * **Controle de Câmera**: A câmera pode ser controlada por movimento do mouse para ajustar o yaw e o pitch[cite: 6]. [cite\_start]A sensibilidade do mouse é configurável[cite: 5].
  * **Manipulação de Objetos**: Permite a translaçãoo (teclas de seta para cima/baixo), rotação (teclas de seta para a esquerda/direita) e escala (teclas +/-) de objetos 3D através de eventos de teclado[cite: 5].
  * **Carregamento de Modelos**: O projeto carrega modelos 3D usando a biblioteca `tinyobjloader`[cite: 4].
  * **Gerenciamento de Janelas e Eventos**: A biblioteca SDL3 é utilizada para criar a janela OpenGL e gerenciar eventos de entrada[cite: 5].

## Pré-requisitos

O projeto utiliza o `vcpkg` como gerenciador de pacotes para gerenciar as dependências[cite: 3]. As dependências do projeto são:

  * `glm` 
  * `sdl3` 
  * `sdl3-image`
  * `sdl3-ttf`
  * `tinyobjloader`
  * `yaml-cpp`
  * `opencv`

Para sistemas baseados em Linux, um script (`dependencies.sh`) está disponível para instalar as dependências de construção necessárias, como `build-essential`, `bison` e as bibliotecas GLX, X11 e Mesa[cite: 2].

O projeto também utiliza CMake para o sistema de build[cite: 4].

## Estrutura de Arquivos

  * `main.cpp`: Ponto de entrada da aplicação que inicializa o aplicativo, carrega a configuração e inicia o loop de renderização.
  * `AugmentedReality.cpp`: Define a classe principal da aplicação, responsável por gerenciar a inicialização da SDL, o contexto OpenGL, o pipeline gráfico, o loop principal e o tratamento de eventos.
  * `Camera.cpp`: Contém a implementação da classe `Camera`, que processa o movimento do mouse para atualizar a orientação da câmera.
  * `vcpkg.json`: Arquivo de manifesto do `vcpkg` que lista todas as dependências do projeto.
  * `CMakeLists.txt`: Arquivo de build do CMake que define as fontes, o executável e as dependências do projeto.
  * `CMakePresets.json`: Define presets de configuração e build para diferentes plataformas (Windows, Linux, macOS) e configurações (Debug, Release).

## Como Compilar e Executar

Este projeto utiliza o CMake para a compilação e o Vcpkg para gerenciar as dependências.

### 1\. Instalar as Dependências

Primeiro, você precisa ter o Vcpkg instalado e configurado[cite: 2]. Se estiver no Linux, você pode usar o script de dependências para configurar o Vcpkg e as bibliotecas do sistema.

#### No Linux
Antes de executar os scripts, é necessário garantir que eles tenham permissão de execução.
No terminal, abra a pasta raiz do projeto (onde os scripts estão localizados) e rode:
```sh
# Dar permissão de execução aos scripts
chmod +x dependencies.sh
chmod +x systemLinuxDependencies.sh

# Executar o script para instalar dependências relacionadas ao vcpkg
./dependencies.sh

# Executar o script para instalar dependências do sistema
./systemLinuxDependencies.sh

```

#### No Windows

Siga as instruções de instalação do Vcpkg [aqui](https://vcpkg.io/en/getting-started.html). Certifique-se de definir a variável de ambiente `VCPKG_ROOT`.

### 2\. Configurar o Projeto

O projeto já inclui o arquivo `CMakePresets.json` para facilitar a configuração. Você pode usar o preset apropriado para o seu sistema.

```sh
# Exemplo para Windows com preset x64-debug
cmake --preset x64-debug

# Exemplo para Linux
cmake --preset linux-debug
```

### 3\. Compilar

Após a configuração, compile o projeto usando o CMake.

```sh
# Compilar o projeto
cmake --build out/build/x64-debug
```

(Substitua `x64-debug` pelo preset que você usou na etapa anterior).

### 4\. Executar

## Antes de executar certifique-se qual é a versão do OpenGL instalada no seu sistema, pois o projeto foi desenvolvido com OpenGL 4.10 ou superior.
O executável será gerado no diretório de build. O arquivo principal é `AugmentedReality`.

```sh
# Exemplo de execução (caminho pode variar)
./out/build/x64-debug/AugmentedReality.exe
```

A aplicação irá carregar as configurações do arquivo `config.yaml` e executar no modo especificado[cite: 1].
