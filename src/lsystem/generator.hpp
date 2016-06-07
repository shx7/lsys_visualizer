#ifndef LSYSTEM_VERTEX_GENERATOR
#define LSYSTEM_VERTEX_GENERATOR

#define GLM_FORCE_RADIANS

#include "GL/glew.h"
#include "GL/glext.h"
#include "GL/gl.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "graphic_object.hpp"
#include "grammar_util.hpp"
#include "generator_symbol_types.hpp" 

#include <memory>

//#include <tuple>
#include <vector>
#include <map>

namespace lsystem
{
    typedef GLfloat Angle;
    typedef GLfloat DeltaAngle;

    /**
     *  lsystem::DrawState incapsulates state of 3D turtle interpeter.
     */
    struct DrawState
    {
        glm::vec3 currentPosition;
        glm::vec3 up, head, left;
        GLfloat deltaAngle;
    };

    /**
     *  lsystem::VertexGenerator convertes string
     *  gained after simulation of lsystem::Simulator
     *  into vertices.
     *
     *  Also VertexGenerator support public interface for
     *  registering drawing user-defined callbacks for symbols.
     *  After generation returns GraphicObject
     */
    class VertexGenerator
    {
        //typedef void (*DrawCommandFunction)(VertexGenerator &);

        public:
            typedef std::function<void(Symbol const &)> DrawingFunction;

            static VertexGenerator &getInstance();

            void initDrawCommands();

            void setDrawState(DrawState const &state);

            void setSymbols(SymbolsPtr const &symbolsPtr);

            GraphicObjectPtr generateGraphicObject();

            void drawLine();

            void drawLine(GLfloat angle);

            void drawSpace();

            void drawSpace(GLfloat angle);

            void yawLeft();

            void yawLeft(GLfloat angle);

            void yawRight();

            void yawRight(GLfloat angle);

            void pitchDown();

            void pitchDown(GLfloat angle);

            void pitchUp();

            void pitchUp(GLfloat angle);

            void rollLeft();

            void rollLeft(GLfloat angle);

            void rollRight();

            void rollRight(GLfloat angle);

            void saveDrawState();

            void restoreDrawState();

            void addDrawingFunction(
                    Symbol const &symbol, DrawingFunction const &fn);

        private:
            VertexGenerator();

            void rotateAroundAxis(glm::vec3 const &axis, GLfloat angle);

            void addVertex(glm::vec3 vertexCoord);

        private:
            std::map< Symbol, DrawingFunction > drawCommands;
            SymbolsPtr symbolsPtr;
            DrawState drawState;
            glm::vec2 imageLeftCorner, imageRightCorner;
            std::vector< glm::vec4 > vertices;
            std::vector< DrawState > drawStateStack;

            const GLfloat limbSize = 0.05; // Defines size of line
            static VertexGenerator instance;
    };
}

#endif
