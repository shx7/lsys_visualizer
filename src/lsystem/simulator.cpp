#include "simulator.hpp"

using namespace lsystem;

Simulator Simulator::instance;

Simulator &Simulator::getInstance()
{
    return instance;
}

Simulator::Simulator()
    : stepCount(0)
    , startAngle(0.0f)
    , deltaAngle(0.0f)
    , startPoint(0.0, 0.0, 0.0)
    , up(0.0, 1.0, 0.0)
    , head(0.0, 0.0, -1.0)
    , left(-1.0, 0.0, 0.0)
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
                std::make_pair(production.producingSymbol.getName(), production));

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
Simulator::getGraphicObject(
          VertexGenerator &generator
        , GLfloat imageWidth
        , GLfloat imageHeight)
{
    generator.setSymbols(generateSymbolsSequence());
    generator.setDrawState({
              startPoint
            , up
            , head
            , left
            , deltaAngle
        });
    generator.setImageRectangle(imageWidth, imageHeight);
    return generator.generateGraphicObject();
}

SymbolsPtr
Simulator::generateSymbolsSequence()
{
    SymbolsPtr result = std::make_shared< Symbols >();
    Symbols processedSymbolsString(axiom);
    for (std::size_t i = 0; i < stepCount; i++)
    { 
        applyProductions(processedSymbolsString);
    }
    result->swap(processedSymbolsString);
    return result;
}

void
Simulator::applyProductions(Symbols &symbols)
{
    Symbols result; 
    for (Symbol const &symbol : symbols)
    {
        auto it = productions.find(symbol.getName());
        if (it != productions.end())
        {
            it->second.appendProductionResult(symbol, result);
        }
        else
        {
            result.push_back(symbol);
        }
    }
    result.swap(symbols);
}

void
Simulator::setUp(glm::vec3 const &v)
{
    up = v;
}

void
Simulator::setHead(glm::vec3 const &v)
{
    head = v;
}

void
Simulator::setLeft(glm::vec3 const &v)
{
    left = v;
}
