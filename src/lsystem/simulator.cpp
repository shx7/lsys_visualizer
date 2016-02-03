#include "simulator.hpp"

using namespace lsystem;

Simulator::Simulator()
    : stepCount(0)
    , startAngle(0.0f)
    , deltaAngle(0.0f)
    , startPoint(0.0, 0.0, 0.0)
{
}

void
Simulator::setAxiom(std::string const &axiom)
{
    processedString.assign(axiom);
}

void
Simulator::addProduction(char character, std::string const &production)
{
    productions[character] = production;
}

void
Simulator::clearProdutions()
{
    productions.clear();
}

void
Simulator::addCommand(char character, std::string const &command)
{
    commands[character] = command;
}

void
Simulator::clearCommands()
{
    commands.clear();
}

void
Simulator::setStepCount(std::size_t stepCount)
{
    this->stepCount = stepCount;
}

void
Simulator::setStartAngle(GLfloat angle)
{
    startAngle = angle;
}

void
Simulator::setDeltaAngle(GLfloat angle)
{
    deltaAngle = angle;
}

void
Simulator::setStartPoint(glm::vec3 startPoint)
{
    this->startPoint = startPoint;
}

GraphicObjectPtr
Simulator::getGraphicObject(GLfloat imageWidth, GLfloat imageHeight)
{
    VertexGenerator generator;
    simulate(); 
    generator.setCommandsString(processedString);
    generator.setDrawState(std::make_tuple(startPoint, startAngle, deltaAngle));
    generator.setImageRectangle(imageWidth, imageHeight);
    return generator.generateGraphicObject();
}

void
Simulator::simulate()
{
    for (std::size_t i = 0; i < stepCount; i++)
    { 
        processedString = mapString(productions);
    }
    processedString = mapString(commands);
}

std::string
Simulator::mapString(CharacterTransitionMap const &map)
{
    std::string result;
    for (char producing_character : processedString)
    {
        auto it = map.find(producing_character);

        if (it != map.end())
        {
            result.append(it->second);
        }
        else
        {
            std::string error_msg = "Unknown command \'";
            error_msg += producing_character;
            error_msg += "\'";
            throw std::runtime_error(error_msg);
        }
    }
    return result;
}
