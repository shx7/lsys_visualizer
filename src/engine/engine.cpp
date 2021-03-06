#include "engine.hpp"

void mouseMovementCallback(GLFWwindow*, double xpos, double ypos)
{
    Camera::instance()->processMouseMovementInput(xpos, ypos);
}

void mouseScrollCallback(GLFWwindow *, double, double yoffset)
{
    Camera::instance()->processMouseScrollInput(yoffset);
}

void keyboardCallback(GLFWwindow *, int key, int, int action, int)
{
    Camera::instance()->processKeyboardInput(key, action);
}

GraphicEngine::GraphicEngine(GLfloat viewportWidth, GLfloat viewportHeight)
    : isGLFWInitialized(false)
    , wnd(nullptr)
    , viewportWidth(viewportWidth)
    , viewportHeight(viewportHeight)
    , vertexShaderId(0)
    , fragmentShaderId(0)
    , programId(0)
    , positionId(-1)
    , colorId(-1)
    , backgroundColor(0.1f, 0.2f, 0.3f, 1.0f)
{
}

GraphicEngine::~GraphicEngine()
{
    if (isGLFWInitialized)
    {
        if (wnd != nullptr)
        {
            glfwDestroyWindow(wnd);
        }
        glfwTerminate();
    }
}

void
GraphicEngine::init(std::string const &logFilename
        , std::string const &vertexShaderFilename
        , std::string const &fragmentShaderFilename)
{
    try
    {
        initLog(logFilename);
        initGLFW();
        initGLEW();
        initCamera();
        initShaders(vertexShaderFilename, fragmentShaderFilename);

        log << "Graphic engine initialized" << std::endl;
    }
    // TODO: fix error with log init
    catch (std::runtime_error const &ex)
    {
        std::cerr << ex.what() << std::endl;
        log << ex.what() << std::endl;
    }
}

void
GraphicEngine::initShaders(std::string const &vertexShaderFilename
                         , std::string const &fragmentShaderFilename)
{
    vertexShaderId = loadShader(vertexShaderFilename, GL_VERTEX_SHADER);
    fragmentShaderId = loadShader(fragmentShaderFilename, GL_FRAGMENT_SHADER);
    linkProgram();

    positionId = getGLAttribute("position");
    colorId = getGLAttribute("color");
}

GLint
GraphicEngine::getGLAttribute(std::string const &attributeName)
{
    GLint result = -1;

    result = glGetAttribLocation(programId, attributeName.c_str());
    if (result < 0)
    {
        throw std::runtime_error("GL attribute not found: " + attributeName);
    }
    return result;
}

GLint
GraphicEngine::getGLUniformAttribute(std::string const &attributeName)
{
    GLint result = -1;

    result = glGetUniformLocation(programId, attributeName.c_str());
    if (result < 0)
    {
        throw std::runtime_error(
                "GL uniform attribute not found: " + attributeName);
    }
    return result;
}

GLuint
GraphicEngine::loadShader(std::string const &filename, GLenum shaderType)
{
    GLuint result = glCreateShader(shaderType);

    std::ifstream inputStream(filename, std::ios_base::in);
    if (!inputStream.is_open())
    {
        throw std::runtime_error("Failed to open file " + filename);
    }

    log << "Load shader from " << filename << std::endl; 
    std::string tmp;
    std::string shaderText("");
    while (std::getline(inputStream, tmp))
    {
        shaderText += tmp;
        shaderText.append("\n");
    }

    compileShader(result, shaderText);

    return result;
}

void
GraphicEngine::compileShader(GLuint shaderId, std::string const &shaderText)
{
    log << "Compile shader" << std::endl;
    char const *shaderTextPtr = shaderText.c_str();
    glShaderSource(shaderId, 1, &shaderTextPtr, nullptr);
    glCompileShader(shaderId);

    GLint result = GL_FALSE;
    GLint infoLogLength = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (GL_FALSE == result)
    {
        log << "Shader compilation error" << std::endl;

        std::vector< char > errorMessage(infoLogLength + 1);
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, &errorMessage[0]); 
        log << "Shader compilation message: "
            << &errorMessage[0] << std::endl;
        throw std::runtime_error("Fault to compile shader");
    }

    log << "Shader compiled" << std::endl; 
}

void
GraphicEngine::linkProgram()
{ 
    programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId); 

    GLint result = GL_FALSE;
    GLint infoLogLength = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (GL_FALSE == result)
    { 
        std::vector< char > errorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programId, infoLogLength, nullptr, &errorMessage[0]); 
        log << "Shader program linking error message: "
            << &errorMessage[0] << std::endl;

        throw std::runtime_error("Fault to link shader program");
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    glUseProgram(programId);
    log << "Shader program linked" << std::endl;
}

void
GraphicEngine::initLog(std::string const &filename)
{
    log.open(filename, std::ios_base::out);

    if (!log.is_open())
    {
        throw std::runtime_error("Failed to open logfile");
    }
}

void
GraphicEngine::initGLFW()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    wnd = glfwCreateWindow(viewportWidth, viewportHeight,
            "LSystems", nullptr, nullptr);
    if (!wnd)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetWindowPos(wnd, 100, 100);
    glfwMakeContextCurrent(wnd);
    glViewport(0, 0, viewportWidth, viewportHeight);

    isGLFWInitialized = true;
}

void
GraphicEngine::initGLEW()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to init GLEW");
    }
}

void
GraphicEngine::initCamera()
{
    glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(wnd, mouseMovementCallback);
    glfwSetScrollCallback(wnd, mouseScrollCallback);
    glfwSetKeyCallback(wnd, keyboardCallback);
}

void
GraphicEngine::initProjectionMatrix()
{
    projectionMatrix = glm::perspective(
              glm::radians(60.0f)
            , viewportHeight / (GLfloat)viewportWidth
            , minClippingDistance
            , maxClippingDistance);

    GLint projectionId = getGLUniformAttribute("proj");
    glUniformMatrix4fv(
              projectionId
            , 1
            , GL_FALSE
            , glm::value_ptr(projectionMatrix));
}

// TODO: optimize here
void
GraphicEngine::updateCamera()
{
    GLint viewLocation = getGLUniformAttribute("view");
    glUniformMatrix4fv(
              viewLocation
            , 1
            , GL_FALSE
            , glm::value_ptr(Camera::instance()->getLookAtMatrix())
            );
}

void
GraphicEngine::start()
{
    initProjectionMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(backgroundColor.r
               , backgroundColor.g
               , backgroundColor.b
               , backgroundColor.a);
    while (!glfwWindowShouldClose(wnd)
            && glfwGetKey(wnd, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        updateCamera();

        for (GraphicObjectPtr ptr : graphicObjects)
        {
            drawObject(ptr);
        }

        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }

    glfwTerminate();
}

void
GraphicEngine::drawObject(GraphicObjectPtr const &ptr)
{
    glBindVertexArray(ptr->getVAOIdentifier());
    glDrawArrays(ptr->getDrawMode(), 0, ptr->getVertexCount() / 6);
    glBindVertexArray(0);
}

void
GraphicEngine::addGraphicObject(GraphicObjectPtr const &ptr)
{
    std::size_t objectVertexCount = ptr->getVertexCount();
    GLfloat const *objectRawVertices = ptr->getRawPointer();

    GLuint objectVBO = 0;
    glGenBuffers(1, &objectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, objectVBO);
    glBufferData(GL_ARRAY_BUFFER, objectVertexCount * sizeof(GLfloat),
            objectRawVertices, GL_STATIC_DRAW);

    GLuint objectVAO = 0;
    glGenVertexArrays(1, &objectVAO);
    glBindVertexArray(objectVAO);

    glEnableVertexAttribArray(positionId);
    glVertexAttribPointer(
            positionId,
            4,
            GL_FLOAT,
            GL_FALSE,
            7 * sizeof(GLfloat),
            0
            );

    glEnableVertexAttribArray(colorId);
    glVertexAttribPointer(
            colorId,
            3,
            GL_FLOAT,
            GL_FALSE,
            7 * sizeof(GLfloat),
            (void *)(4 * sizeof(GLfloat))
            );
    glBindVertexArray(0);

    ptr->setVAOIdentifier(objectVAO);
    graphicObjects.push_back(ptr);
}
