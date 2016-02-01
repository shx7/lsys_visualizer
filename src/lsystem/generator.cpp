#include "generator.hpp"
using namespace lsystem;

VertexGenerator::
VertexGenerator(GLfloat width, GLfloat height)
    : width(width)
    , height(height)
{
    initDrawCommands();
}

void
VertexGenerator::initDrawCommands()
{
    drawCommands['F'] = [&] (DrawState &state, GraphicObjectPtr ptr)
    {
        glm::vec3 currentPosition = state.first;
        ptr->addVertex(glm::vec3(currentPosition), glm::vec3(0.0, 0.0, 0.0));
        currentPosition.x += 1;
        ptr->addVertex(glm::vec3(currentPosition), glm::vec3(0.0, 1.0, 0.0));
    };
}

void
VertexGenerator::setImageRectangle(GLfloat width, GLfloat height)
{
    this->width = width;
    this->height = height;
}

void
VertexGenerator::setCommandsString(std::string const &commands)
{
    cmdString = commands;
}

GraphicObjectPtr
VertexGenerator::generateGraphicObject()
{
    GraphicObjectPtr result(new GraphicObject());
    DrawState drawState = std::make_pair(glm::vec3(0.0, 0.0, 0.0), 0.0f);

    for (char ch : cmdString)
    {
        drawCommands[ch](drawState, result);
    }

    return result;
}
