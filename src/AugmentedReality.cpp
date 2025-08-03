// AugmentedReality.cpp: define o ponto de entrada para o aplicativo.
//

#include "AugmentedReality.h"

void GLAPIENTRY OpenGLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") << " type = " << type << ", severity = " << severity << ", message = " << message << std::endl;
}


AugmentedReality::AugmentedReality() {
	// Constructor implementation
}
// Substitua SDL_GL_DeleteContext_renamed_SDL_GL_DestroyContext por SDL_GL_DeleteContext
// O nome correto da função é SDL_GL_DeleteContext


AugmentedReality::~AugmentedReality() {
	// Destructor implementation
	if (glContext) {
		SDL_GL_DestroyContext(glContext); // Corrigido para o nome correto
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}

bool AugmentedReality::InitializeSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    // Define the OpenGL context attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    window = SDL_CreateWindow(
        "OpenGL window with SDL3 and glad",
        windowWidth, windowHeight,
        SDL_WINDOW_OPENGL
    );
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }
    return true;
}


void AugmentedReality::Run() {
	// Main loop implementation
    while (running) {
        // Pre-draw setup
        PreDraw(modelMatrix);
        // Draw the triangle
        Draw();
		// Handle events like keyboard input, mouse movement, etc.
        HandleEvents();
    }
}

void AugmentedReality::GetOpenGLVersionInfo()
{
    std::cout << "OpenGL Version Information:" << std::endl;
    const GLubyte* version = glGetString(GL_VERSION);
    if (version) {
        std::cout << "OpenGL Version: " << version << std::endl;
    }
    else {
        std::cerr << "Failed to retrieve OpenGL version." << std::endl;
    }
    const GLubyte* vendor = glGetString(GL_VENDOR);
    if (vendor) {
        std::cout << "OpenGL Vendor: " << vendor << std::endl;
    }
    else {
        std::cerr << "Failed to retrieve OpenGL vendor." << std::endl;
    }
    const GLubyte* renderer = glGetString(GL_RENDERER);
    if (renderer) {
        std::cout << "OpenGL Renderer: " << renderer << std::endl;
    }
    else {
        std::cerr << "Failed to retrieve OpenGL renderer." << std::endl;
    }
    const GLubyte* shadingLanguageVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    if (shadingLanguageVersion) {
        std::cout << "OpenGL Shading Language Version: " << shadingLanguageVersion << std::endl;
    }
    else {
        std::cerr << "Failed to retrieve OpenGL shading language version." << std::endl;
    }
}

void AugmentedReality::VertexSpecification()
{
    // Generate and bind the Vertex Array Object (VAO)
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // VBO de posições
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 
                  object.GetVertices().size() * sizeof(GLfloat), 
                  object.GetVertices().data(), 
                  GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // VBO de cores
    glGenBuffers(1, &vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glBufferData(GL_ARRAY_BUFFER, 
                 object.GetVerticesColors().size() * sizeof(GLfloat), 
                 object.GetVerticesColors().data(), 
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// VBO de texturas
	glGenBuffers(1, &vboTextures);
	glBindBuffer(GL_ARRAY_BUFFER, vboTextures);
	glBufferData(GL_ARRAY_BUFFER, 
                object.GetVerticesTextureCoords().size() * sizeof(GLfloat), 
                object.GetVerticesTextureCoords().data(), 
                GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, object.GetIndices().size() * sizeof(GLuint), object.GetIndices().data(), GL_STATIC_DRAW);

    // Unbind the VBO and EBO
    glBindVertexArray(0);

}

void AugmentedReality::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
            exit(0);
        }
        // Verifica se uma tecla foi pressionada
        if (event.type == SDL_EVENT_KEY_DOWN) {
            SDL_Keycode key = event.key.key;
            //std::cout << "Tecla pressionada: " << SDL_GetKeyName(key) << std::endl;
            // Exemplo: sair ao pressionar ESC
            if (key == SDLK_ESCAPE) {
                running = false;
                exit(0);
            }
            else if (key == SDLK_UP) {
                offsetZ = 0.1f; // Incrementa o offset Z
                //std::cout << "Offset Y aumentado: " << offsetZ << std::endl;
            }
            else if (key == SDLK_DOWN) {
                offsetZ = -0.1f; // Decrementa o offset Z
                //std::cout << "Offset Y diminuído: " << offsetZ << std::endl;
            }
            else if (key == SDLK_LEFT) {
                rotationAngle -= 5.0f; // Decrementa o ângulo de rotação
                //std::cout << "Ângulo de rotação diminuído: " << rotationAngle << std::endl;
            }
            else if (key == SDLK_RIGHT) {
                rotationAngle += 5.0f; // Incrementa o ângulo de rotação
                //std::cout << "Ângulo de rotação aumentado: " << rotationAngle << std::endl;
            }
            else if (key == SDLK_PLUS || key == SDLK_KP_PLUS) {
                scaleFactor += 0.1f; // Incrementa o fator de escala
                //std::cout << "Fator de escala aumentado: " << scaleFactor << std::endl;
            }
            else if (key == SDLK_MINUS || key == SDLK_KP_MINUS) {
                scaleFactor -= 0.1f; // Decrementa o fator de escala
                //std::cout << "Fator de escala diminuído: " << scaleFactor << std::endl;
            }
        }
        else if (event.type == SDL_EVENT_MOUSE_MOTION) {
            // Obtenha o deslocamento do mouse
            int deltaX = event.motion.xrel;
            int deltaY = event.motion.yrel;

            // Sensibilidade do mouse (ajuste conforme necessário)
            const float sensitivity = 1.0f;

            // Atualize o ângulo de visão da câmera
            camera.processMouseMovement(static_cast<float>(deltaX) * sensitivity,
                static_cast<float>(-deltaY) * sensitivity);

            //std::cout << "Mouse movimento: deltaX=" << deltaX << " deltaY=" << deltaY << std::endl;
        }
    }
}

void AugmentedReality::CreateGraphicsPipeline(const std::string vertexShaderFileName,const std::string fragmentShaderFileName,bool debugOn)
{
    // Create the shader program
	//object.LoadTexture("C:\\Users\\dnune\\OneDrive\\Documentos\\Visual Studio 2022\\Projects\\AugmentedReality\\images\\simprao.bmp", window); // Load texture if needed
    object.LoadTexture("", window); // Load texture if needed
    graphicsPipelineShaderProgram = shaderOps.CreateShaderProgramFromFiles(vertexShaderFileName, fragmentShaderFileName);
    if (graphicsPipelineShaderProgram == 0) {
        std::cerr << "Failed to create shader program." << std::endl;
        return;
    }
    // Generate and bind the Vertex Array Object (VAO)
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // Generate and bind the Vertex Buffer Object (VBO)
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Define vertex data
    VertexSpecification();
    // Unbind the VAO
    glBindVertexArray(0);

    if (debugOn) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);
    }
}

void AugmentedReality::PreDraw(glm::mat4& lModelMatrix)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, windowWidth, windowHeight);
    // Clear the screen
    glClearColor(cfg.backgroundColor.r, cfg.backgroundColor.g, cfg.backgroundColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    // Use the shader program
    glUseProgram(graphicsPipelineShaderProgram);
    // Set the uniform for the offset
    glm::mat4 translation = glm::translate(lModelMatrix, glm::vec3(0.0f, 0.0f, offsetZ));
    offsetZ = 0.0f; // Reset offset after applying it
    glm::mat4 rotate = glm::rotate(translation, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 scale = glm::scale(rotate, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    lModelMatrix = scale;
    glm::mat4 perspective = glm::perspective(glm::radians(camera.mFov), camera.mAspectRatio, camera.mNear, camera.mFar);

    // Set the uniform for the model matrix
    // Note: Ensure that the shader program has the uniform variables defined
    // Get the uniform locations
    GLint uModelMatrixLocation = glGetUniformLocation(graphicsPipelineShaderProgram, "uModelMatrix");
    GLint uPerspectiveMatrixLocation = glGetUniformLocation(graphicsPipelineShaderProgram, "uPerspectiveMatrix");
    GLint uViewMatrixLocation = glGetUniformLocation(graphicsPipelineShaderProgram, "uViewMatrix");
	GLint uTextureLocation = glGetUniformLocation(graphicsPipelineShaderProgram, "uTexture");

    if (uModelMatrixLocation != -1) {
        glUniformMatrix4fv(uModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(lModelMatrix));
    }
    else {
        std::cerr << "Uniform 'uModelMatrix' not found in shader program." << std::endl;
        std::exit(EXIT_FAILURE); // Exit if the texture uniform is not found
    }
    if (uPerspectiveMatrixLocation != -1) {
        glUniformMatrix4fv(uPerspectiveMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
    }
    else {
        std::cerr << "Uniform 'uPerspectiveMatrix' not found in shader program." << std::endl;
        std::exit(EXIT_FAILURE); // Exit if the texture uniform is not found
    }
    if (uViewMatrixLocation != -1) {
        glUniformMatrix4fv(uViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
    }
    else {
        std::cerr << "Uniform 'uViewMatrix' not found in shader program." << std::endl;
        std::exit(EXIT_FAILURE); // Exit if the texture uniform is not found
    }
    if (uTextureLocation != -1) {
        glUniform1i(uTextureLocation, 0); // Assuming texture unit 0
    }
    else {
        std::cerr << "Uniform 'uTexture' not found in shader program." << std::endl;
		std::exit(EXIT_FAILURE); // Exit if the texture uniform is not found
	}
    // Bind the VAO
    glBindVertexArray(vao);
}

void AugmentedReality::Draw()
{
    // Draw the triangle
    //glDrawArrays(GL_TRIANGLES, 0, verticesSize);
    glDrawElements(GL_TRIANGLES, object.GetVerticesSize(), GL_UNSIGNED_INT, 0);
    // Unbind the VAO
    glBindVertexArray(0);
    // Swap buffers
    SDL_GL_SwapWindow(window);
}
