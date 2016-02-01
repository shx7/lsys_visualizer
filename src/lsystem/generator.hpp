#ifndef LSYSTEM_VERTEX_GENERATOR
#define LSYSTEM_VERTEX_GENERATOR

#include "graphic_object.hpp"

#include <memory>

#include <tuple>
#include <unordered_map>

namespace lsystem
{
    typedef GLfloat Angle;
    typedef GLfloat DeltaAngle;
    typedef std::tuple< glm::vec3, Angle, DeltaAngle > DrawState;
    typedef void (* DrawCommandFunction)(DrawState &, GraphicObjectPtr);

    class VertexGenerator
    {
        public:
            VertexGenerator(GLfloat width = 0, GLfloat height = 0);

            void initDrawCommands();

            void setImageRectangle(GLfloat width, GLfloat height);

            void setDrawState(DrawState const &state);

            void setCommandsString(std::string const &commands);

            GraphicObjectPtr generateGraphicObject();

        private:
            GLfloat width, height;
            std::unordered_map< char, DrawCommandFunction > drawCommands;
            std::string cmdString;
            DrawState drawState;
    };
}

#endif
