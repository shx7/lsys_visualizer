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
Simulator::setAxiom(Symbols const &axiom)
{
    this->axiom = axiom;
}

void
Simulator::addProduction(Production const &production)
{
    auto res = productions.insert(
                std::make_pair(production.producingSymbol.name, production));

    if (!res.second)
    {
        throw std::runtime_error("Adding already added production");
    }
}

void
Simulator::clearProdutions()
{
    productions.clear();
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
    generator.setCommandsString(generateCommands());
    //generator.setCommandsString(processedString);
    //generator.setDrawState(std::make_tuple(startPoint, startAngle, deltaAngle));
    //generator.setImageRectangle(imageWidth, imageHeight);
    //return generator.generateGraphicObject();
    return GraphicObjectPtr();
}

CommandsPtr
Simulator::generateCommands()
{
    Symbols processedSymbolsString(axiom);
    for (std::size_t i = 0; i < stepCount; i++)
    { 
        applyProductions(processedSymbolsString);
    }
    return symbolsToCommands(processedSymbolsString);
}

void
Simulator::applyProductions(Symbols &symbols)
{
    Symbols result; 
    for (Symbol const &symbol : symbols)
    {
        auto it = productions.find(symbol.name);
        if (it == productions.end())
        {
            throw std::runtime_error("No production for such symbol");
        }
        it->second.appendProductionResult(symbol, result);
    }
    result.swap(symbols);
}

CommandsPtr
Simulator::symbolsToCommands(Symbols const &symbols)
{
    CommandsPtr result(new Commands);

    for (Symbol const &symbol : symbols)
    {
        result->insert( 
                result->begin(),
                symbol.drawCommands->begin(),
                symbol.drawCommands->end());
    }
    return result;
}
