# Projeto AugmentedRealityCpp

Este projeto � uma aplica��o de Realidade Aumentada desenvolvida em C++ que utiliza OpenGL para renderiza��o 3D e SDL3 para gerenciamento de janelas e eventos. [cite\_start]Ele tamb�m possui funcionalidades para manipula��o de c�meras e objetos 3D, e integra bibliotecas como OpenCV para manipula��es de imagem e GLM para matem�tica de vetores e matrizes[cite: 5].

## Sobre o Projeto

[cite\_start]A aplica��o � configur�vel atrav�s de um arquivo YAML (`config.yaml`) e pode operar em diferentes modos, como "OpenGL" e "OpenCV"[cite: 1].

As principais funcionalidades incluem:

  * [cite\_start]**Renderiza��o 3D**: Utiliza OpenGL 3.1 com um pipeline de renderiza��o configurado para desenhar objetos 3D[cite: 5].
  * [cite\_start]**Controle de C�mera**: A c�mera pode ser controlada por movimento do mouse para ajustar o yaw e o pitch[cite: 6]. [cite\_start]A sensibilidade do mouse � configur�vel[cite: 5].
  * [cite\_start]**Manipula��o de Objetos**: Permite a transla��o (teclas de seta para cima/baixo), rota��o (teclas de seta para a esquerda/direita) e escala (teclas +/-) de objetos 3D atrav�s de eventos de teclado[cite: 5].
  * [cite\_start]**Carregamento de Modelos**: O projeto carrega modelos 3D usando a biblioteca `tinyobjloader`[cite: 4].
  * [cite\_start]**Gerenciamento de Janelas e Eventos**: A biblioteca SDL3 � utilizada para criar a janela OpenGL e gerenciar eventos de entrada[cite: 5].

## Pr�-requisitos

[cite\_start]O projeto utiliza o `vcpkg` como gerenciador de pacotes para gerenciar as depend�ncias[cite: 3]. As depend�ncias do projeto s�o:

  * [cite\_start]`glm` [cite: 3]
  * [cite\_start]`sdl3` [cite: 3]
  * [cite\_start]`sdl3-image` [cite: 3]
  * [cite\_start]`sdl3-ttf` [cite: 3]
  * [cite\_start]`tinyobjloader` [cite: 3]
  * [cite\_start]`yaml-cpp` [cite: 3]
  * [cite\_start]`opencv` [cite: 3]

[cite\_start]Para sistemas baseados em Linux, um script (`dependencies.sh`) est� dispon�vel para instalar as depend�ncias de constru��o necess�rias, como `build-essential`, `bison` e as bibliotecas GLX, X11 e Mesa[cite: 2].

[cite\_start]O projeto tamb�m utiliza CMake para o sistema de build[cite: 4].

## Estrutura de Arquivos

  * [cite\_start]`main.cpp`: Ponto de entrada da aplica��o que inicializa o aplicativo, carrega a configura��o e inicia o loop de renderiza��o[cite: 1].
  * [cite\_start]`AugmentedReality.cpp`: Define a classe principal da aplica��o, respons�vel por gerenciar a inicializa��o da SDL, o contexto OpenGL, o pipeline gr�fico, o loop principal e o tratamento de eventos[cite: 5].
  * [cite\_start]`Camera.cpp`: Cont�m a implementa��o da classe `Camera`, que processa o movimento do mouse para atualizar a orienta��o da c�mera[cite: 6].
  * [cite\_start]`vcpkg.json`: Arquivo de manifesto do `vcpkg` que lista todas as depend�ncias do projeto[cite: 3].
  * [cite\_start]`CMakeLists.txt`: Arquivo de build do CMake que define as fontes, o execut�vel e as depend�ncias do projeto[cite: 4].
  * `CMakePresets.json`: Define presets de configura��o e build para diferentes plataformas (Windows, Linux, macOS) e configura��es (Debug, Release).

## Como Compilar e Executar

Este projeto utiliza o CMake para a compila��o e o Vcpkg para gerenciar as depend�ncias.

### 1\. Instalar as Depend�ncias

[cite\_start]Primeiro, voc� precisa ter o Vcpkg instalado e configurado[cite: 2]. Se estiver no Linux, voc� pode usar o script de depend�ncias para configurar o Vcpkg e as bibliotecas do sistema.

#### No Linux

```sh
# Executar o script para instalar depend�ncias do sistema e configurar o vcpkg
./dependencies.sh
```

#### No Windows

Siga as instru��es de instala��o do Vcpkg [aqui](https://vcpkg.io/en/getting-started.html). Certifique-se de definir a vari�vel de ambiente `VCPKG_ROOT`.

### 2\. Configurar o Projeto

O projeto j� inclui o arquivo `CMakePresets.json` para facilitar a configura��o. Voc� pode usar o preset apropriado para o seu sistema.

```sh
# Exemplo para Windows com preset x64-debug
cmake --preset x64-debug

# Exemplo para Linux
cmake --preset linux-debug
```

### 3\. Compilar

Ap�s a configura��o, compile o projeto usando o CMake.

```sh
# Compilar o projeto
cmake --build out/build/x64-debug
```

(Substitua `x64-debug` pelo preset que voc� usou na etapa anterior).

### 4\. Executar

[cite\_start]O execut�vel ser� gerado no diret�rio de build[cite: 4]. [cite\_start]O arquivo principal � `AugmentedReality`[cite: 4].

```sh
# Exemplo de execu��o (caminho pode variar)
./out/build/x64-debug/AugmentedReality.exe
```

[cite\_start]A aplica��o ir� carregar as configura��es do arquivo `config.yaml` e executar no modo especificado[cite: 1].