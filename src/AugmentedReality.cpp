// AugmentedReality.cpp: define o ponto de entrada para o aplicativo.
//

#include "AugmentedReality.h"
/**
* @brief Callback function for OpenGL debug messages. 
* 
* @param source The source of the message (e.g., GL_DEBUG_SOURCE_API, GL_DEBUG_SOURCE_SHADER_COMPILER).
* @param type The type of the message (e.g., GL_DEBUG_TYPE_ERROR, GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR).
* @param id The message ID.
* @param severity The severity of the message (e.g., GL_DEBUG_SEVERITY_HIGH, GL_DEBUG_SEVERITY_MEDIUM).
* @param length The length of the message.
* @param message The debug message.
* @param userParam User-defined parameter (not used in this case).
* @note This function prints the OpenGL debug messages to the standard error output.
* @see https://www.khronos.org/opengl/wiki/Debug_Output
* @see https://www.khronos.org/opengl/wiki/Debug_Output#Debug_message_callback
* @note This function is registered as a callback for OpenGL debug messages using `glDebugMessageCallback`.
*/
void GLAPIENTRY OpenGLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") << " type = " << type << ", severity = " << severity << ", message = " << message << std::endl;
}

/**
* @brief Default constructor for the AugmentedReality class.
*/
AugmentedReality::AugmentedReality() {
	// Constructor implementation
}

/**
* @brief Destructor for the AugmentedReality class. 
* @note It cleans up the SDL resources and destroys the OpenGL context.
*/
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

/**
* @brief Initializes the SDL library and creates an OpenGL context.
* @return True if initialization is successful, false otherwise.
* @note This function initializes SDL with video support, sets OpenGL context attributes, creates a window, and initializes GLAD for OpenGL function loading.
* @see https://wiki.libsdl.org/SDL_Init
* @see https://wiki.libsdl.org/SDL_GL_SetAttribute
* @see https://wiki.libsdl.org/SDL_CreateWindow
* @see https://glad.dav1d.de
* @see https://www.youtube.com/watch?v=wg4om77Drr0&list=PLvv0ScY6vfd9zlZkIIqGDeG5TUWswkMox&index=5 youTube video on setting up OpenGL with SDL3 and GLAD
*/
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

/**
* @brief Main running loop for class Augmented Reality.
* @note This function contains the main loop of the application, where it continuously draws the scene and handles events. It needs to kepp running until the user decides to exit application
*/
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

/**
* @brief Retrieves and prints OpenGL version information.
* @note This function queries the OpenGL version, vendor, renderer, and shading language version using `glGetString` and prints them to the console.
* @see https://www.khronos.org/opengl/wiki/Getting_Started#OpenGL_version
* @see https://www.khronos.org/opengl/wiki/GLAPI/glGetString
*/
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

/**
* @brief Sets buffers and vertex attributes for the 3D object.
* @note This function generates and binds Vertex Array Objects (VAOs), Vertex Buffer Objects (VBOs), and Element Buffer Objects (EBOs) for the 3D object. It also sets up vertex attributes for positions, colors, normals, and texture coordinates.
* @see https://www.khronos.org/opengl/wiki/Vertex_Array_Object
* @see https://www.khronos.org/opengl/wiki/Vertex_Buffer_Object
* @see https://www.khronos.org/opengl/wiki/Element_Buffer_Object
* @see https://www.khronos.org/opengl/wiki/Vertex_Attribute
* @see https://www.youtube.com/watch?v=Ktp1P4J04Gw&list=PLvv0ScY6vfd9zlZkIIqGDeG5TUWswkMox&index=6 youTube video on setting up VBOs, VAOs, and EBOs in OpenGL
* @note This function assumes that the `object` member variable has been properly initialized with vertex data, colors, normals, and texture coordinates.
*/

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
    if (object.GetVerticesTextureCoords().size() > 0) {
        std::cout << "Using texture coordinates." << std::endl;
        glGenBuffers(1, &vboTextures);
        glBindBuffer(GL_ARRAY_BUFFER, vboTextures);
        glBufferData(GL_ARRAY_BUFFER,
            object.GetVerticesTextureCoords().size() * sizeof(GLfloat),
            object.GetVerticesTextureCoords().data(),
            GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    } else {
        std::cout << "No texture coordinates provided." << std::endl;
	}    
    // VBO de normais
    glGenBuffers(1, &vboNormals);
    glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
    glBufferData(GL_ARRAY_BUFFER,
        object.GetVerticesNormals().size() * sizeof(GLfloat),
        object.GetVerticesNormals().data(),
        GL_STATIC_DRAW);
    glEnableVertexAttribArray(3); // Local 3 para normais
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, object.GetIndices().size() * sizeof(GLuint), object.GetIndices().data(), GL_STATIC_DRAW);

    // Unbind the VBO and EBO
    glBindVertexArray(0);

}

/**
* @brief Draws the 3D object using OpenGL.
* @note This function manipulates events coming from the user, such as keyboard input and mouse movement. It also sets up the OpenGL context, clears the screen, and draws the object using the shader program.
* @see https://www.khronos.org/opengl/wiki/Rendering
*/
void AugmentedReality::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
            exit(0);
        }
		// Verify if the event is a key down event if user has pressed a key.
        if (event.type == SDL_EVENT_KEY_DOWN) {
            SDL_Keycode key = event.key.key;
			if (key == SDLK_ESCAPE) { // Esc key to exit
                running = false;
                exit(0);
            }
            else if (key == SDLK_UP) {
				offsetZ = 0.1f; // Increase the offset Z
                //std::cout << "Offset Y aumentado: " << offsetZ << std::endl;
            }
            else if (key == SDLK_DOWN) {
                offsetZ = -0.1f; // Decrease the offset Z
                //std::cout << "Offset Y diminuído: " << offsetZ << std::endl;
            }
            else if (key == SDLK_LEFT) {
				rotationAngle = 5.0f; // Decrease the rotation angle
                //std::cout << "Ângulo de rotação diminuído: " << rotationAngle << std::endl;
            }
            else if (key == SDLK_RIGHT) {
				rotationAngle = -5.0f; // Increase the rotation angle
                //std::cout << "Ângulo de rotação aumentado: " << rotationAngle << std::endl;
            }
            else if (key == SDLK_PLUS || key == SDLK_KP_PLUS) {
				scaleFactor = 0.1f; // Increase the scale factor
                //std::cout << "Fator de escala aumentado: " << scaleFactor << std::endl;
            }
            else if (key == SDLK_MINUS || key == SDLK_KP_MINUS) {
				scaleFactor = -0.1f; // Decrease the scale factor
                //std::cout << "Fator de escala diminuído: " << scaleFactor << std::endl;
            }
        }
		// Verify if the event is a mouse motion event if user has moved the mouse.
        else if (event.type == SDL_EVENT_MOUSE_MOTION && cfg.mouseMoveEnabled) {
			// Get the relative motion of the mouse
            int deltaX = event.motion.xrel;
            int deltaY = event.motion.yrel;

			// Sensitivity factor for mouse movement. Load from cconfig file.
            const float sensitivity = cfg.mouseSensitivity;

			// Update the camera's view direction based on mouse movement
            camera.processMouseMovement(static_cast<float>(deltaX) * sensitivity,
                static_cast<float>(-deltaY) * sensitivity);

            //std::cout << "Mouse movimento: deltaX=" << deltaX << " deltaY=" << deltaY << std::endl;
        }
    }
}

/**
* @brief Creates the graphics pipeline by loading shaders and setting up vertex buffers.
* @param vertexShaderFileName The file name of the vertex shader.
* @param fragmentShaderFileName The file name of the fragment shader.
* @param debugOn Whether to enable OpenGL debug output.
* @note This function loads the vertex and fragment shaders from the specified files, creates a shader program, generates and binds Vertex Array Objects (VAOs) and Vertex Buffer Objects (VBOs), and sets up vertex attributes for positions, colors, normals, and texture coordinates.
* @see https://www.khronos.org/opengl/wiki/Shader_Compilation
* @see https://www.youtube.com/watch?v=kpA5X6eI6fM&list=PLvv0ScY6vfd9zlZkIIqGDeG5TUWswkMox&index=4 youTube video on setting up shaders in OpenGL.
*/ 
void AugmentedReality::CreateGraphicsPipeline(const std::string vertexShaderFileName,const std::string fragmentShaderFileName,bool debugOn)
{
    // Create the shader program
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

/**
* @brief Prepares the OpenGL context for drawing the 3D object.
* @param lModelMatrix The model matrix to be used for transformations.
* @note This function sets up the OpenGL context for drawing by disabling depth testing and face culling, clearing the screen, using the shader program, setting uniforms for model, perspective, and view matrices, and binding the VAO. It also applies transformations such as translation, rotation, and scaling to the model matrix.
* @see https://www.khronos.org/opengl/wiki/Matrix_Stack
* @see https://www.khronos.org/opengl/wiki/Uniform
*/
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
	rotationAngle = 0.0f; // Reset rotation angle after applying it
	scaleFactor = 1.0f; // Reset scale factor after applying it
    // Set the uniform for the model matrix
    // Note: Ensure that the shader program has the uniform variables defined
    // Get the uniform locations
    GLint uModelMatrixLocation = glGetUniformLocation(graphicsPipelineShaderProgram, "uModelMatrix");
    GLint uPerspectiveMatrixLocation = glGetUniformLocation(graphicsPipelineShaderProgram, "uPerspectiveMatrix");
    GLint uViewMatrixLocation = glGetUniformLocation(graphicsPipelineShaderProgram, "uViewMatrix");
	GLint uTextureLocation = glGetUniformLocation(graphicsPipelineShaderProgram, "uTexture");
	GLint uLoadTextureLocation = glGetUniformLocation(graphicsPipelineShaderProgram, "uLoadTexture");

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
        if (object.GetTextureID() != -1) {
            glUniform1d(uLoadTextureLocation, 1); // Load the texture ID
        } else {
            glUniform1d(uLoadTextureLocation, 0); // No load the texture ID
		}
    }
    else {
        std::cerr << "Uniform 'uTexture' not found in shader program." << std::endl;
		std::exit(EXIT_FAILURE); // Exit if the texture uniform is not found
	}
    // Bind the VAO
    glBindVertexArray(vao);
}

/**
* @brief Draws the 3D object using OpenGL.
* @note This function draws the 3D object using the bound VAO and the shader program. It uses `glDrawArrays` or `glDrawElements` to render the object based on the vertex data and indices.
* @see https://www.khronos.org/opengl/wiki/Rendering#Drawing
*/
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
