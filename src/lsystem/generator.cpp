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

glm::mat4
VertexGenerator::getTransformMatrix(GLfloat imageWidth, GLfloat imageHeight)
{ 
    glm::vec2 const &screenSize = getScreenSize();
    GLfloat screenWidth = screenSize.x;
    GLfloat screenHeight = screenSize.y;

    GLfloat currentImageWidth = imageRightCorner.x - imageLeftCorner.x;
    GLfloat currentImageHeight = imageRightCorner.y - imageLeftCorner.y;

    GLfloat scaleXCoefficient
        = (2.0f * imageWidth / screenWidth) / currentImageWidth;
    GLfloat scaleYCoefficient
        = (2.0f * imageHeight / screenHeight) / currentImageHeight; 
    glm::mat4 scaleMatrix = glm::scale(
              glm::mat4(1.0)
            , glm::vec3(scaleXCoefficient, scaleYCoefficient, 1.0f));

    // Apply scale transform to image corners to preserve consistent state
    imageLeftCorner = glm::vec2(scaleMatrix * glm::vec4(imageLeftCorner, 0, 1));
    imageRightCorner = glm::vec2(scaleMatrix * glm::vec4(imageRightCorner, 0, 1));

    GLfloat translationX
        = 2.0f * (-imageWidth / 2.0f) / screenWidth - imageLeftCorner.x;
    GLfloat translationY
        = 2.0f * (-imageHeight / 2.0f) / screenHeight - imageLeftCorner.y;
    glm::mat4 translationMatrix = glm::translate(
              glm::mat4(1.0)
            , glm::vec3(translationX, translationY, 0));

    return translationMatrix * scaleMatrix;
}

void
VertexGenerator::scaleImage()
{ 
    glm::mat4 const &transformMatrix = getTransformMatrix(width, height);
    for (glm::vec4 &vertex : vertices)
    {
        vertex = transformMatrix * vertex;
    }
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
        currentPosition.x += 1 * cos(currentAngle);
        currentPosition.y += 1 * sin(currentAngle); 
        generator.addVertex(currentPosition); 

        generator.updateImageCorners();
    };

    drawCommands['f'] = [&] (VertexGenerator &generator)
    {
        glm::vec3& currentPosition = std::get< 0 >(generator.drawState);
        GLfloat currentAngle = std::get< 1 >(generator.drawState);

        currentPosition.x += 1 * cos(currentAngle);
        currentPosition.y += 1 * sin(currentAngle);
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

    drawCommands['['] = [&] (VertexGenerator &generator)
    {
        generator.saveDrawState();
    };

    drawCommands[']'] = [&] (VertexGenerator &generator)
    {
        generator.restoreDrawState();
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

void
VertexGenerator::saveDrawState()
{
    drawStateStack.push_back(drawState);
}

void
VertexGenerator::restoreDrawState()
{
    if (drawStateStack.empty())
    {
        throw std::runtime_error("Production rules error. State stack is empty.");
    }

    drawState = drawStateStack.back();
    drawStateStack.pop_back();
}
