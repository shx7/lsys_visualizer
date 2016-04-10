#include "generator.hpp"
using namespace lsystem;

VertexGenerator::
VertexGenerator(GLfloat width, GLfloat height)
    : width(width)
    , height(height)
{
    drawState = {
          glm::vec3(0.0, 0.0, 0.0)
        , glm::vec3(0.0, 1.0, 0.0)
        , glm::vec3(0.0, 0.0, -1.0)
        , glm::vec3(-1.0, 0.0, 0.0)
        , 0.0f
    };
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
    glm::vec3 &currentPosition = drawState.currentPosition;

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

    GLfloat scaleCoefficient = 1.0f;
    if (currentImageWidth > currentImageHeight)
    {
        scaleCoefficient
            = (2.0f * imageWidth / screenWidth) / currentImageWidth;
        imageHeight *= currentImageHeight / currentImageWidth;
    }
    else
    {
        scaleCoefficient
            = (2.0f * imageHeight / screenWidth) / currentImageHeight;
        imageWidth *= currentImageWidth / currentImageHeight;
    } 

    glm::mat4 scaleMatrix = glm::scale(
              glm::mat4(1.0)
            , glm::vec3(scaleCoefficient, scaleCoefficient, 1.0f));

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
    drawCommands[symbolDrawLine] = [&] (
              VertexGenerator &generator
            , Symbol const &)
    {
        generator.drawLine();
    };

    drawCommands[symbolDrawSpace] = [&] (
              VertexGenerator &generator
            , Symbol const &)
    {
        generator.drawSpace();
    };

    drawCommands[symbolRotateRight] = [&] (
              VertexGenerator &generator
            , Symbol const &)
    {
        generator.rotateRight();
    };

    drawCommands[symbolRotateLeft] = [&] (
              VertexGenerator &generator
            , Symbol const &)
    {
        generator.rotateLeft();
    };

    drawCommands[symbolSaveState] = [&] (
              VertexGenerator &generator
            , Symbol const &)
    {
        generator.saveDrawState();
    };

    drawCommands[symbolRestoreState] = [&] (
              VertexGenerator &generator
            , Symbol const &)
    {
        generator.restoreDrawState();
    };
}

void
VertexGenerator::
drawLine()
{
    glm::vec3& currentPosition = drawState.currentPosition;
    //GLfloat currentAngle = drawState.currentAngle;

    addVertex(currentPosition);
    /*currentPosition.x += 1 * cos(currentAngle);
    currentPosition.y += 1 * sin(currentAngle);*/
    currentPosition += drawState.head;
    addVertex(currentPosition);

    updateImageCorners();
}

void
VertexGenerator::
drawSpace()
{
    glm::vec3& currentPosition = drawState.currentPosition;
    currentPosition += drawState.head;
    /*GLfloat currentAngle = drawState.currentAngle;

    currentPosition.x += 1 * cos(currentAngle);
    currentPosition.y += 1 * sin(currentAngle);*/
}

// TODO: fix rotation
void
VertexGenerator::
rotateRight()
{
    glm::mat4 rotationMatrix
        = rotate(glm::mat4(), drawState.deltaAngle, drawState.left);
    drawState.head = glm::vec3(rotationMatrix * glm::vec4(drawState.head, 1));
    drawState.up = glm::vec3(rotationMatrix * glm::vec4(drawState.up, 1));
    drawState.left = glm::vec3(rotationMatrix * glm::vec4(drawState.left, 1));
    /*GLfloat &currentAngle = drawState.currentAngle;
    GLfloat deltaAngle = drawState.deltaAngle;

    currentAngle -= deltaAngle;*/
}

// TODO: fix rotation
void
VertexGenerator::
rotateLeft()
{
    glm::mat4 rotationMatrix
        = rotate(glm::mat4(), (-1) * drawState.deltaAngle, drawState.left);
    drawState.head = glm::vec3(rotationMatrix * glm::vec4(drawState.head, 1));
    drawState.up = glm::vec3(rotationMatrix * glm::vec4(drawState.up, 1));
    drawState.left = glm::vec3(rotationMatrix * glm::vec4(drawState.left, 1));
    /*GLfloat &currentAngle = drawState.currentAngle;
    GLfloat deltaAngle = drawState.deltaAngle;

    currentAngle += deltaAngle;*/
}

void
VertexGenerator::setImageRectangle(GLfloat width, GLfloat height)
{
    this->width = width;
    this->height = height;
}

void
VertexGenerator::setSymbols(SymbolsPtr const &symbolsPtr)
{
    this->symbolsPtr = symbolsPtr;
}

GraphicObjectPtr
VertexGenerator::generateGraphicObject()
{
    GraphicObjectPtr result(new GraphicObject());
    glm::vec3 vertexColor = glm::vec3(0.4396f, 0.75686f, 0.13725f);

    for (Symbol symbol : (*symbolsPtr))
    {
        drawCommands[symbol](*this, symbol);
    }
    //scaleImage();

    for (glm::vec4 vertex : vertices)
    {
        result->addVertex(vertex, vertexColor);
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

void
VertexGenerator::
addDrawingFunction(Symbol const &symbol, DrawingFunction const &fn)
{
    drawCommands[symbol] = fn;
}
