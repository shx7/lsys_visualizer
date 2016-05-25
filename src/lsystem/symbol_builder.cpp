#include "symbol_builder.hpp"

using namespace lsystem;

std::string SymbolBuilder::currentSymbolName = "a";

SymbolBuilder
SymbolBuilder::
getBuilder(VertexGenerator &generator, Simulator &simulator)
{
    return SymbolBuilder(getNextName(), generator, simulator);
}

SymbolBuilder
SymbolBuilder::
getBuilder(VertexGenerator &generator
        , Simulator &simulator
        , Symbol const &symbol)
{
    return SymbolBuilder(symbol, generator, simulator);
}

SymbolBuilder::
SymbolBuilder(std::string const &name
        , lsystem::VertexGenerator &generator
        , lsystem::Simulator &simulator)
    : symbol(name)
    , generator(generator)
    , simulator(simulator)
{
}

SymbolBuilder::
SymbolBuilder(Symbol const &symbol
        , lsystem::VertexGenerator &generator
        , lsystem::Simulator &simulator)
    : symbol(symbol)
    , generator(generator)
    , simulator(simulator)
{
}

SymbolBuilder&
SymbolBuilder::
addParameter(std::string const &name, GLfloat value)
{
    symbol.addParameter(name, value);
    return *this;
}

// TODO: add stochastic fn
SymbolBuilder &
SymbolBuilder::
setProduction(ProducingFunction const &fn, GLfloat probability)
{
    Production production(symbol, probability, fn);
    simulator.addProduction(production);
    return *this;
}

SymbolBuilder &
SymbolBuilder::
setDrawingFunction(
        VertexGenerator::DrawingFunction const &fn)
{
    generator.addDrawingFunction(symbol, fn);
    return *this;
}

Symbol
SymbolBuilder::
build()
{
    return symbol;
}

std::string
SymbolBuilder::
getNextName()
{
    if (currentSymbolName[currentSymbolName.size() - 1] == 'z' + 1)
    {
        std::string tmp(currentSymbolName.size() + 1, 'a');
        tmp.swap(currentSymbolName);
    }
    std::string res = incCurrentSymbolName();
    return res;
}

std::string
SymbolBuilder::
incCurrentSymbolName()
{
    std::string tmp = currentSymbolName;
    currentSymbolName[currentSymbolName.size() - 1]++;
    return tmp;
}
