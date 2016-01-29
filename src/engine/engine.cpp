#include "engine.hpp"

GraphicEngine::GraphicEngine(std::string const &logFilename)
    : wnd(nullptr)
    , viewportWidth(0)
    , viewportHeight(0)
{
    init(logFilename);
}

void
GraphicEngine::init(std::string const &logFilename)
{
    try
    {
        initLog(logFilename);
        initGLFW();
        initGLEW();
    }
    catch (std::runtime_error const &ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    log << "Graphic engine initialized" << std::endl;
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
}

void
GraphicEngine::drawObject(GraphicObjectPtr const &ptr)
{
}

void
GraphicEngine::processInput()
{
}

void
GraphicEngine::addGraphicObject(GraphicObjectPtr const &ptr)
{
}
