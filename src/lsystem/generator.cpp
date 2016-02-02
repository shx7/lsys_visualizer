#include "generator.hpp"
#include <iostream>
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
    updateImageCorners();
}

void
VertexGenerator::updateImageCorners()
{
    glm::vec3 &currentPosition = std::get< 0 >(drawState);

    if (currentPosition.x < imageLeftCorner.x)
    {
        imageLeftCorner.x = currentPosition.x;
    }

    if (currentPosition.y < imageLeftCorner.y)
    {
        imageLeftCorner.y = currentPosition.y;
    }

    if (currentPosition.x > imageRightCorner.x)
    {
        imageRightCorner.x = currentPosition.x;
    }

    if (currentPosition.y > imageRightCorner.y)
    {
        imageRightCorner.y = currentPosition.y;
    }
}

void
VertexGenerator::addVertex(glm::vec3 vertex)
{
    vertices.push_back(glm::vec4(vertex, 1));
}

glm::vec2
VertexGenerator::getImageSize()
{
    glm::vec2 const &screenSize = getScreenSize();
    GLfloat screenWidth = screenSize.x;
    GLfloat screenHeight = screenSize.y;

    GLfloat rawImageWidth =
        screenWidth * (imageRightCorner.x - imageLeftCorner.x) / 2.0f;
    GLfloat rawImageHeight =
        screenHeight * (imageRightCorner.y - imageLeftCorner.y) / 2.0f;

    return glm::vec2(rawImageWidth, rawImageHeight);
}

void
VertexGenerator::scaleImage()
{
    glm::vec2 imageSize = getImageSize();

    GLfloat scaleXCoefficient = width / imageSize.x;
    GLfloat scaleYCoefficient = height / imageSize.y;

    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),
            glm::vec3(scaleXCoefficient, scaleYCoefficient, 1.0f));

    for (glm::vec4 &vertex : vertices)
    {
        vertex = scaleMatrix * vertex;
    }
}

void
VertexGenerator::centerImage()
{
}

glm::vec2
VertexGenerator::getScreenSize()
{
    GLint windowOptions[4];
    glGetIntegerv(GL_VIEWPORT, &windowOptions[0]);
    return glm::vec2(windowOptions[2], windowOptions[3]);
}

void
VertexGenerator::initDrawCommands()
{

    drawCommands['F'] = [&] (VertexGenerator &generator)
    {
        glm::vec3& currentPosition = std::get< 0 >(generator.drawState);
        GLfloat currentAngle = std::get< 1 >(generator.drawState);

        generator.addVertex(currentPosition); 
        currentPosition.x += 0.01 * cos(currentAngle);
        currentPosition.y += 0.01 * sin(currentAngle); 
        generator.addVertex(currentPosition); 

        generator.updateImageCorners();
    };

    drawCommands['f'] = [&] (VertexGenerator &generator)
    {
        glm::vec3& currentPosition = std::get< 0 >(generator.drawState);
        GLfloat currentAngle = std::get< 1 >(generator.drawState);

        currentPosition.x += 0.01 * cos(currentAngle);
        currentPosition.y += 0.01 * sin(currentAngle);
    };

    drawCommands['+'] = [&] (VertexGenerator &generator)
    {
        GLfloat &currentAngle = std::get< 1 >(generator.drawState);
        GLfloat deltaAngle = std::get< 2 >(generator.drawState);

        currentAngle -= deltaAngle;
    };

    drawCommands['-'] = [&] (VertexGenerator &generator)
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
        drawCommands[ch](*this);
    }
    scaleImage();

    for (glm::vec4 vertex : vertices)
    {
        result->addVertex(glm::vec3(vertex), glm::vec3(0.0, 1.0, 0.0));
    }
    result->setDrawMode(GL_LINES);

    return result;
}
