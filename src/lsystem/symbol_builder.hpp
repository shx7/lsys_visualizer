#ifndef SYMBOL_BUILDER_HPP
#define SYMBOL_BUILDER_HPP

#include "generator.hpp"
#include "simulator.hpp"
#include "symbol.hpp"

namespace lsystem
{
    /**
     *  lsystem::SymbolBuilder is responsible for creation, customization and
     *  registration Symbols elements in Simulator and VertexGenerator.
     *
     *  After Symbol creation new object is immutable.
     *
     *  Example:
     *  \code
     * 
     *  lsystem::Symbol symbolX =
     *      lsystem::SymbolBuilder::getBuilder()
     *      .setDrawingFunction(
     *          [&] (lsystem::Symbol const &)
     *          {
     *              generator.drawLine();
     *          })
     *      .setProduction(
     *          [=] (lsystem::Symbol const &s) -> lsystem::Symbols
     *          {
     *              lsystem::Symbol tmp(s);
     *              lsystem::Symbols result;
     *              result.push_back(symbolF);
     *              result.push_back(lsystem::symbolSaveState);
     *              result.push_back(lsystem::getSymbolYawLeft(
     *                          glm::radians(20.0),
     *                          [](double param) -> double
     *                          {
     *                              return param * 0.85;
     *                          }, 0.8)
     *                      );
     *              result.push_back(tmp);
     *              result.push_back(lsystem::symbolRestoreState);
     *
     *              result.push_back(lsystem::symbolSaveState);
     *              result.push_back(lsystem::getSymbolPitchUp(
     *                          glm::radians(20.0),
     *                          [](double param) -> double
     *                          {
     *                              return param * 0.95;
     *                          }, 0.8)
     *                      );
     *              result.push_back(tmp);
     *              result.push_back(lsystem::symbolRestoreState);
     *
     *              result.push_back(symbolF);
     *              result.push_back(lsystem::symbolSaveState);
     *              result.push_back(
     *                  lsystem::getSymbolYawRight(glm::radians(20.0), 0.0, 0.7));
     *              result.push_back(tmp);
     *              result.push_back(lsystem::symbolRestoreState);
     *
     *              result.push_back(lsystem::symbolSaveState);
     *              result.push_back(lsystem::symbolPitchDown);
     *              result.push_back(tmp);
     *              result.push_back(lsystem::symbolRestoreState);
     *
     *              result.push_back(lsystem::symbolYawLeft);
     *              result.push_back(tmp);
     *              return result;
     *          }, 0.95)
     *      .build();
     *  \endcode
     */
    class SymbolBuilder
    {
        public:
            static SymbolBuilder getBuilder();

            static SymbolBuilder getBuilder(Symbol const &symbol);

            SymbolBuilder(std::string const &name
                    , lsystem::VertexGenerator &generator
                    , lsystem::Simulator &simulator);

            SymbolBuilder(Symbol const &symbol
                    , lsystem::VertexGenerator &generator
                    , lsystem::Simulator &simulator);

            SymbolBuilder& addParameter(std::string const &name, GLfloat value);

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
