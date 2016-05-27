#ifndef SYMBOL_LIBRARY_HPP
#define SYMBOL_LIBRARY_HPP

#include "symbol_builder.hpp"

namespace lsystem
{
    Symbol const &getSymbolYawRight(double initialAngle
            , double deltaAngle
            , double probability = 1.0)
    {
        static Symbol result
            = SymbolBuilder::getBuilder()
            .addParameter("angle", initialAngle)
            .setProduction(
                [=] (Symbol const &s) -> Symbols
                {
                    Symbols res;
                    Symbol tmp(s);
                    auto &param_value = s["angle"];
                    param_value += deltaAngle;
                    res.push_back(s);
                    return res;
                })
            .setDrawingFunction(
                [=] (VertexGenerator &g, Symbol const &s)
                {
                    g.yawRight(s["angle"]);
                })
            .build();
        return result;
    }
} // lsystem

#endif
