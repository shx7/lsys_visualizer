#include "generator.hpp"
using namespace lsystem;

VertexGenerator VertexGenerator::instance;

VertexGenerator &
VertexGenerator::
getInstance()
{
    return instance;
}

VertexGenerator::
VertexGenerator()
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
}

void
VertexGenerator::addVertex(glm::vec3 vertex)
{
    vertices.push_back(glm::vec4(vertex, 1));
}

void
VertexGenerator::initDrawCommands()
{ 
    addDrawingFunction(symbolDrawLine,
        [&] (Symbol const &)
            {
                VertexGenerator::getInstance().drawLine();
            });

    addDrawingFunction(symbolDrawSpace,
        [&] (Symbol const &)
            {
                VertexGenerator::getInstance().drawSpace();
            });

    addDrawingFunction(symbolPitchDown,
        [&] (Symbol const &)
            {
                VertexGenerator::getInstance().pitchDown();
            });

    addDrawingFunction(symbolPitchUp,
        [&] (Symbol const &)
            {
                VertexGenerator::getInstance().pitchUp();
            });

    addDrawingFunction(symbolYawRight,
        [&] (Symbol const &)
            {
                VertexGenerator::getInstance().yawRight();
            });

    addDrawingFunction(symbolYawLeft,
        [&] (Symbol const &)
            {
                VertexGenerator::getInstance().yawLeft();
            });

    addDrawingFunction(symbolRollLeft,
        [&] (Symbol const &)
            {
                VertexGenerator::getInstance().rollLeft();
            });

    addDrawingFunction(symbolRollRight,
        [&] (Symbol const &)
            {
                VertexGenerator::getInstance().rollRight();
            });

    addDrawingFunction(symbolSaveState,
        [&] (Symbol const &)
            {
                VertexGenerator::getInstance().saveDrawState();
            });

    addDrawingFunction(symbolRestoreState,
        [&] (Symbol const &)
            {
                getInstance().restoreDrawState();
            });
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
    currentPosition += drawState.head * limbSize;
    addVertex(currentPosition);
}

void
VertexGenerator::
drawSpace()
{
    glm::vec3& currentPosition = drawState.currentPosition;
    currentPosition += drawState.head * limbSize;
    /*GLfloat currentAngle = drawState.currentAngle;

    currentPosition.x += 1 * cos(currentAngle);
    currentPosition.y += 1 * sin(currentAngle);*/
}

// TODO: fix rotation
void
VertexGenerator::
yawLeft()
{
    rotateAroundAxis(drawState.up, (-1) * drawState.deltaAngle);
}

void
VertexGenerator::
yawLeft(GLfloat angle)
{
    rotateAroundAxis(drawState.up, (-1) * angle);
}

void
VertexGenerator::
yawRight()
{
    rotateAroundAxis(drawState.up, drawState.deltaAngle);
}

void
VertexGenerator::
yawRight(GLfloat angle)
{
    rotateAroundAxis(drawState.up, angle);
}

void
VertexGenerator::
pitchDown()
{
    rotateAroundAxis(drawState.left, drawState.deltaAngle);
}

void
VertexGenerator::
pitchDown(GLfloat angle)
{
    rotateAroundAxis(drawState.left, angle);
}

void
VertexGenerator::
pitchUp()
{
    rotateAroundAxis(drawState.left, (-1) * drawState.deltaAngle);
}

void
VertexGenerator::
pitchUp(GLfloat angle)
{
    rotateAroundAxis(drawState.left, (-1) * angle);
}

void
VertexGenerator::
rollLeft()
{
    rotateAroundAxis(drawState.head, (-1) * drawState.deltaAngle);
}

void
VertexGenerator::
rollLeft(GLfloat angle)
{
    rotateAroundAxis(drawState.head, (-1) * angle);
}

void
VertexGenerator::
rollRight()
{
    rotateAroundAxis(drawState.head, drawState.deltaAngle);
}

void
VertexGenerator::
rollRight(GLfloat angle)
{
    rotateAroundAxis(drawState.head, angle);
}

void
VertexGenerator::
rotateAroundAxis(glm::vec3 const &axis, GLfloat angle)
{
    glm::mat4 rotationMatrix
        = glm::rotate(glm::mat4(), angle, axis);
    drawState.head = glm::vec3(rotationMatrix * glm::vec4(drawState.head, 1));
    drawState.up = glm::vec3(rotationMatrix * glm::vec4(drawState.up, 1));
    drawState.left = glm::vec3(rotationMatrix * glm::vec4(drawState.left, 1));
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
        drawCommands[symbol](symbol);
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
