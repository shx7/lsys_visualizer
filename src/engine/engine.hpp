/***********************************************
 *
 * GraphicEngine used for representation
 * registered list of GraphicObject's by
 * OpenGL >= 3.0
 ***********************************************/
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <list>
#include <vector>

#include "graphic_object.hpp"
#include "camera.hpp"

class GraphicEngine
{ 
    public:
        GraphicEngine(GLfloat viewportWidth = 640
                    , GLfloat viewportHeight = 480);

        ~GraphicEngine();

        void init(std::string const &logFilename
                , std::string const &vertexShaderFilename
                , std::string const &fragmentShaderFilename);

        void start();

        void addGraphicObject(GraphicObjectPtr const &ptr);

    private:
        void drawObject(GraphicObjectPtr const &ptr);

        void initLog(std::string const &filename);

        void initGLFW();

        void initGLEW();

        void initShaders(
                  std::string const &vertexShaderFilename
                , std::string const &fragmentShaderFilename);

        void initCamera();

        GLuint loadShader(std::string const &filename, GLenum shaderType);

        void compileShader(GLuint shaderId, std::string const &shaderText);

        void linkProgram();

        GLint getGLAttribute(std::string const &attributeName);

        GLint getGLUniformAttribute(std::string const &attributeName);

        void updateCamera();

    private:
        bool isGLFWInitialized;
        std::fstream log;
        GLFWwindow* wnd;

        std::list< GraphicObjectPtr > graphicObjects;
        int viewportWidth, viewportHeight;

        GLuint vertexShaderId, fragmentShaderId, programId;
        GLint positionId, colorId;

        glm::vec4 backgroundColor;
};

extern void mouseCallback(GLFWwindow* wnd, double xpos, double ypos);

extern void keyboardCallback(
          GLFWwindow *wnd
        , int key
        , int scancode
        , int action
        , int mods);

#endif
