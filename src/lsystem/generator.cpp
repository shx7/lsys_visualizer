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
    updateRawImageCorners();
}

void
VertexGenerator::updateRawImageCorners()
{
    vec3 &currentPosition = std::get< 0 >(drawState);

    if (currentPosition.x < imageLeftCorner.x
            || currentPosition.y < imageLeftCorner.y)
    {
        imageLeftCorner = glm::vec2(currentPosition);
    }

    if (currentPosition.x > imageRightCorner.x
            || currentPosition.y > imageRightCorner.y)
    {
        imageRightCorner = glm::vec2(currentPosition);
    }
}

void
VertexGenerator::initDrawCommands()
{

    drawCommands['F'] = [&] (VertexGenerator &generator, GraphicObjectPtr ptr)
    {
        glm::vec3& currentPosition = std::get< 0 >(generator.drawState);
        GLfloat currentAngle = std::get< 1 >(generator.drawState);

        ptr->addVertex(currentPosition, glm::vec3(0.0, 1.0, 0.0)); 

        currentPosition.x += 0.01 * cos(currentAngle);
        currentPosition.y += 0.01 * sin(currentAngle); 

        ptr->addVertex(currentPosition, glm::vec3(0.0, 1.0, 0.0));

        glm::vec2 &imageLeftCorner = generator.imageLeftCorner;
        updateRawImageCorners();
    };

    drawCommands['f'] = [&] (VertexGenerator &generator, GraphicObjectPtr)
    {
        glm::vec3& currentPosition = std::get< 0 >(generator.drawState);
        GLfloat currentAngle = std::get< 1 >(generator.drawState);

        currentPosition.x += 0.01 * cos(currentAngle);
        currentPosition.y += 0.01 * sin(currentAngle);
    };

    drawCommands['+'] = [&] (VertexGenerator &generator, GraphicObjectPtr)
    {
        GLfloat &currentAngle = std::get< 1 >(generator.drawState);
        GLfloat deltaAngle = std::get< 2 >(generator.drawState);

        currentAngle -= deltaAngle;
    };

    drawCommands['-'] = [&] (VertexGenerator &generator, GraphicObjectPtr)
    {
        GLfloat &currentAngle = std::get< 1 >(generator.drawState);
        GLfloat deltaAngle = std::get< 2 >(generator.drawState);

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
        drawCommands[ch](*this, result);
    }
    result->setDrawMode(GL_LINES);

    return result;
}
