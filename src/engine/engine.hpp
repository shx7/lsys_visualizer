#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <list>
#include <memory>

#include "graphic_object.hpp"

typedef std::shared_ptr< GraphicObject > GraphicObjectPtr;

class GraphicEngine
{ 
    public:
        GraphicEngine(std::string const &logFilename);

        void init(std::string const &logFilename);

        void start();

        void addGraphicObject(GraphicObjectPtr const &ptr);

    private:
        void drawObject(GraphicObjectPtr const &ptr);

        void processInput();

        void initLog(std::string const &filename);
        void initGLFW();
        void initGLEW();

    private:
        std::fstream log;
        GLFWwindow* wnd;

        std::list< GraphicObjectPtr > graphicObjects;
        int viewportWidth, viewportHeight;
};

#endif
