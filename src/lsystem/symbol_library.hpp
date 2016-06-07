#ifndef SYMBOL_LIBRARY_HPP
#define SYMBOL_LIBRARY_HPP

#include <functional>

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

    Symbol const &getSymbolPitchUp(double initialAngle
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
                    g.pitchUp(s["angle"]);
                })
            .build();
        return result;
    }


    Symbol const &getSymbolPitchDown(double initialAngle
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
                    g.pitchDown(s["angle"]);
                })
            .build();
        return result;
    }


    Symbol const &getSymbolRollRight(double initialAngle
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
                    g.rollRight(s["angle"]);
                })
            .build();
        return result;
    }

    Symbol const &getSymbolRollLeft(double initialAngle
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
                    g.rollLeft(s["angle"]);
                })
            .build(); 
        return result;
    }


    // Functional symbols
    Symbol const &getSymbolYawRight(double initialAngle
            , std::function<double(double)> fn
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
                    param_value = fn(param_value);
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
            , std::function<double(double)> fn
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
                    param_value = fn(param_value);
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

    Symbol const &getSymbolPitchUp(double initialAngle
            , std::function<double(double)> fn
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
                    param_value = fn(param_value);
                    res.push_back(tmp);
                    return res;
                }, probability)
            .setDrawingFunction(
                [=] (Symbol const &s)
                {
                    lsystem::VertexGenerator &g
                        = lsystem::VertexGenerator::getInstance();
                    g.pitchUp(s["angle"]);
                })
            .build();
        return result;
    }


    Symbol const &getSymbolPitchDown(double initialAngle
            , std::function<double(double)> fn
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
                    param_value = fn(param_value);
                    res.push_back(tmp);
                    return res;
                }, probability)
            .setDrawingFunction(
                [=] (Symbol const &s)
                {
                    lsystem::VertexGenerator &g
                        = lsystem::VertexGenerator::getInstance();
                    g.pitchDown(s["angle"]);
                })
            .build();
        return result;
    }


    Symbol const &getSymbolRollRight(double initialAngle
            , std::function<double(double)> fn
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
                    param_value = fn(param_value);
                    res.push_back(tmp);
                    return res;
                }, probability)
            .setDrawingFunction(
                [=] (Symbol const &s)
                {
                    lsystem::VertexGenerator &g
                        = lsystem::VertexGenerator::getInstance();
                    g.rollRight(s["angle"]);
                })
            .build();
        return result;
    }

    Symbol const &getSymbolRollLeft(double initialAngle
            , std::function<double(double)> fn
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
                    param_value = fn(param_value);
                    res.push_back(tmp);
                    return res;
                }, probability)
            .setDrawingFunction(
                [=] (Symbol const &s)
                {
                    lsystem::VertexGenerator &g
                        = lsystem::VertexGenerator::getInstance();
                    g.rollLeft(s["angle"]);
                })
            .build(); 
        return result;
    }
} // lsystem

#endif
