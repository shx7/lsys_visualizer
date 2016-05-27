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
                    auto &param_value = tmp["angle"];
                    param_value += deltaAngle;
                    res.push_back(tmp);
                    return res;
                }, probability)
            .setDrawingFunction(
                [=] (Symbol const &s)
                {
                    lsystem::VertexGenerator &g
                        = lsystem::VertexGenerator::getInstance();
                    g.yawRight(s["angle"]);
                })
            .build();
        return result;
    }

    Symbol const &getSymbolYawLeft(double initialAngle
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
                    auto &param_value = tmp["angle"];
                    param_value += deltaAngle;
                    res.push_back(tmp);
                    return res;
                }, probability)
            .setDrawingFunction(
                [=] (Symbol const &s)
                {
                    lsystem::VertexGenerator &g
                        = lsystem::VertexGenerator::getInstance();
                    g.yawLeft(s["angle"]);
                })
            .build();
        return result;
    }
} // lsystem

#endif
