#include "generator.hpp"
using namespace lsystem;

VertexGenerator::
VertexGenerator(GLfloat width, GLfloat height)
    : width(width)
    , height(height)
{
    drawState = std::make_tuple(glm::vec3(0.0, 0.0, 0.0), 0.0f, 0.0f);
    initDrawCommands();
}

void
VertexGenerator::setDrawState(DrawState const &state)
{
    drawState = state;
}

void
VertexGenerator::initDrawCommands()
{
    drawCommands['F'] = [&] (DrawState &state, GraphicObjectPtr ptr)
    {
        glm::vec3& currentPosition = std::get< 0 >(state);
        GLfloat currentAngle = std::get< 1 >(state);

        ptr->addVertex(glm::vec3(currentPosition), glm::vec3(0.0, 1.0, 0.0)); 
        currentPosition.x += 0.01 * cos(currentAngle);
        currentPosition.y += 0.01 * sin(currentAngle); 
        ptr->addVertex(glm::vec3(currentPosition), glm::vec3(0.0, 1.0, 0.0));
    };

    drawCommands['f'] = [&] (DrawState &state, GraphicObjectPtr)
    {
        glm::vec3& currentPosition = std::get< 0 >(state);
        GLfloat currentAngle = std::get< 1 >(state);

        currentPosition.x += 0.01 * cos(currentAngle);
        currentPosition.y += 0.01 * sin(currentAngle);
    };

    drawCommands['+'] = [&] (DrawState &state, GraphicObjectPtr)
    {
        GLfloat &currentAngle = std::get< 1 >(state);
        GLfloat deltaAngle = std::get< 2 >(state);

        currentAngle -= deltaAngle;
    };

    drawCommands['-'] = [&] (DrawState &state, GraphicObjectPtr)
    {
        GLfloat &currentAngle = std::get< 1 >(state);
        GLfloat deltaAngle = std::get< 2 >(state);

        currentAngle += deltaAngle;
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

    for (char ch : cmdString)
    {
        drawCommands[ch](drawState, result);
    }
    result->setDrawMode(GL_LINES);

    return result;
}
