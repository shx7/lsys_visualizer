#include "engine.hpp"

GraphicEngine::GraphicEngine()
    : isGLFWInitialized(false)
    , wnd(nullptr)
    , viewportWidth(0)
    , viewportHeight(0)
    , vertexShaderId(0)
    , fragmentShaderId(0)
    , programId(0)
    , positionId(-1)
    , colorId(-1)
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
    wnd = glfwCreateWindow(640, 480, "LSystems", nullptr, nullptr);
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
GraphicEngine::start()
{
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    while (!glfwWindowShouldClose(wnd)
            && glfwGetKey(wnd, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    { 
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }

    glfwTerminate();
}

void
GraphicEngine::drawObject(GraphicObjectPtr const &ptr)
{
    glBindVertexArray(ptr->getVAOIdentifier());
    glBindVertexArray(0);
}

void
GraphicEngine::processInput()
{
}

void
GraphicEngine::addGraphicObject(GraphicObjectPtr const &ptr)
{
    std::size_t objectVertexCount = ptr->getVertexCount();
    GLfloat const *objectRawVertices = ptr->getRawPointer();

    GLuint objectVBO = 0;
    glGenBuffers(1, &objectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, objectVBO);
    glBufferData(GL_ARRAY_BUFFER, objectVertexCount,
            objectRawVertices, GL_STATIC_DRAW);

    GLuint objectVAO = 0;
    glGenVertexArrays(1, &objectVAO);
    glBindVertexArray(objectVAO);

    glEnableVertexAttribArray(positionId);
    glVertexAttribPointer(
            positionId,
            3,
            GL_FLOAT,
            GL_FALSE,
            5 * sizeof(GL_FLOAT),
            0
            );

    glEnableVertexAttribArray(colorId);
    glVertexAttribPointer(
            colorId,
            2,
            GL_FLOAT,
            GL_FALSE,
            5 * sizeof(GL_FLOAT),
            (void *)(2 * sizeof(GL_FLOAT))
            );
    glBindVertexArray(0);

    ptr->setVAOIdentifier(objectVAO);
    graphicObjects.push_back(ptr);
}
