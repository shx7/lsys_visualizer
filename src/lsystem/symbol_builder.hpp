#ifndef SYMBOL_BUILDER_HPP
#define SYMBOL_BUILDER_HPP

#include "generator.hpp"
#include "simulator.hpp"
#include "symbol.hpp"

namespace lsystem
{
    class SymbolBuilder
    {
        public:
            static SymbolBuilder getBuilder(
                      VertexGenerator &generator
                    , Simulator &simulator);

            static SymbolBuilder getBuilder(
                      VertexGenerator &generator
                    , Simulator &simulator
                    , Symbol const &symbol);

            SymbolBuilder(std::string const &name
                    , lsystem::VertexGenerator &generator
                    , lsystem::Simulator &simulator);

            SymbolBuilder(Symbol const &symbol
                    , lsystem::VertexGenerator &generator
                    , lsystem::Simulator &simulator);

            SymbolBuilder& addParameter(std::string const &name, GLfloat value);

            // TODO: add stochastic fn
            SymbolBuilder &setProduction(ProducingFunction const &fn
                    , GLfloat probability = 1.0);

            SymbolBuilder &setDrawingFunction(
                    VertexGenerator::DrawingFunction const &fn);

            Symbol build();

        private:
            // TODO: replace Name with ID
            static std::string getNextName();

            static std::string incCurrentSymbolName();

        private:
            Symbol symbol;
            VertexGenerator &generator;
            Simulator &simulator;
            static std::string currentSymbolName;
    };
} // lsystem

#endif
