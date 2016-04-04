/************************************************
 *
 * lsystem::VertexGenerator convertes string
 * gained after simulation of lsystem::Simulator
 * into vertices.
 *
 * Also VertexGenerator implements functions
 * scaling and translation image to the center of
 * OpenGL window.
 ***********************************************/
#ifndef LSYSTEM_VERTEX_GENERATOR
#define LSYSTEM_VERTEX_GENERATOR

#include "graphic_object.hpp"
#include "grammar_util.hpp"

#include "GL/gl.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

#include <tuple>
#include <vector>
#include <unordered_map>

namespace lsystem
{
    typedef GLfloat Angle;
    typedef GLfloat DeltaAngle;
    typedef std::tuple< glm::vec3, Angle, DeltaAngle > DrawState;

    class VertexGenerator
    {
        typedef void (*DrawCommandFunction)(VertexGenerator &);

        public:
            VertexGenerator(GLfloat width = 640, GLfloat height = 480);

            void initDrawCommands();

            void setImageRectangle(GLfloat width, GLfloat height);

            void setDrawState(DrawState const &state);

            void setCommandsString(CommandsPtr const &commandsPtr);

            GraphicObjectPtr generateGraphicObject();

            void drawLine();

            void drawSpace();

            void rotateLeft();

            void rotateRight();

            void saveDrawState();

            void restoreDrawState();

        private:
            void updateImageCorners();

            void scaleImage();

            void addVertex(glm::vec3 vertexCoord);

            glm::vec2 getScreenSize();

            glm::mat4 getTransformMatrix(GLfloat imageWidth, GLfloat imageHeight);

        private:
            GLfloat width, height;
            std::unordered_map< char, DrawCommandFunction > drawCommands;
            CommandsPtr cmdString;
            DrawState drawState;
            glm::vec2 imageLeftCorner, imageRightCorner;
            std::vector< glm::vec4 > vertices;
            std::vector< DrawState > drawStateStack;
    };
}

#endif
