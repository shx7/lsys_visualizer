#ifndef LSYSTEM_VERTEX_GENERATOR
#define LSYSTEM_VERTEX_GENERATOR

#include "graphic_object.hpp"

#include <memory>
#include <unordered_map>

namespace lsystem
{
    typedef std::pair< glm::vec3, GLfloat > DrawState;
    typedef void (* DrawCommandFunction)(DrawState &, GraphicObjectPtr);

    class VertexGenerator
    {
        public:
            VertexGenerator(GLfloat width, GLfloat height);

            void initDrawCommands();

            void setImageRectangle(GLfloat width, GLfloat height);

            void setCommandsString(std::string const &commands);

            GraphicObjectPtr generateGraphicObject();

        private:
            GLfloat width, height;
            std::unordered_map< char, DrawCommandFunction > drawCommands;
            std::string cmdString;
    };
}

#endif
