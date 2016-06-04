#include <iostream>
#include "engine.hpp"
#include "generator.hpp"
#include "simulator.hpp"

#include "grammar_util.hpp"
#include "symbol_builder.hpp"
#include "generator_symbol_types.hpp"

#include "symbol_library.hpp"

#include "glm/gtc/constants.hpp"

// P-Lsystem test
/*void simpleTree1()
{
    std::string vertexShaderFilename("../src/shaders/vertex_shader.vert");
    std::string fragmentShaderFilename("../src/shaders/fragment_shader.frag");
    GraphicEngine engine;
    engine.init("logfile", vertexShaderFilename, fragmentShaderFilename);

    lsystem::Simulator simulator;
    lsystem::Symbols axiom;

    // Base branch
    lsystem::Symbol symbolBase("BaseBranch");
    symbolBase.addParameter("width", 1);

    // Lateral branch
    lsystem::Symbol symbolLateralBranch("LateralBranch");

    lsystem::Symbol symbolOffshoot("Offshoot");

    axiom.push_back(symbolBase);
    simulator.setAxiom(axiom);
    simulator.setStartPoint(glm::vec3(0, 0, 0));

    simulator.setHead(glm::vec3(0, 1, 0));
    simulator.setUp(glm::vec3(0, 0, -1));
    simulator.setLeft(glm::vec3(-1, 0, 0));
    simulator.setDeltaAngle(glm::quarter_pi< GLfloat > ());

    lsystem::VertexGenerator generator;
    generator.addDrawingFunction(symbolBase,
            [] (lsystem::VertexGenerator &g, lsystem::Symbol const &s)
            {
                GLfloat width = s["width"];
                for (int i = 0; i < width; ++i)
                {
                    g.drawLine();
                }
            });

    lsystem::Production productionS(symbolBase, 0.1,
            [&] (lsystem::Symbol const& s) -> lsystem::Symbols
            {
                lsystem::Symbols result;
                lsystem::Symbol tmp(s);
                auto& s_width = tmp["width"];
                s_width += 1;
                result.push_back(tmp);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolYawLeft);
                result.push_back(s);
                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolYawRight);
                result.push_back(symbolLateralBranch);
                result.push_back(lsystem::symbolRestoreState);
                result.push_back(lsystem::symbolYawRight);
                result.push_back(s);
                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolPitchDown);
                result.push_back(symbolLateralBranch);
                result.push_back(lsystem::symbolPitchDown);
                result.push_back(lsystem::symbolPitchDown);
                result.push_back(s);
                result.push_back(lsystem::symbolRestoreState);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolYawRight);
                result.push_back(s);
                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolYawRight);
                result.push_back(symbolLateralBranch);
                result.push_back(lsystem::symbolRestoreState);
                result.push_back(lsystem::symbolYawRight);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolPitchDown);
                result.push_back(symbolLateralBranch);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolYawLeft);
                return result;
            });
    simulator.addProduction(productionS);

    generator.addDrawingFunction(symbolLateralBranch,
            [] (lsystem::VertexGenerator &g, lsystem::Symbol const &s)
            {
                g.drawLine();
            });

    simulator.addProduction(
    lsystem::Production(symbolLateralBranch, 0.1,
            [&] (lsystem::Symbol const& s) -> lsystem::Symbols
            {
                lsystem::Symbols result;
                result.push_back(s);
                result.push_back(s);
                return result;
            })
    );

    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::radians(35.0));
    simulator.setStartAngle(glm::half_pi< GLfloat >());

    simulator.setStepCount(2);
    engine.addGraphicObject(
            simulator.getGraphicObject(generator, 640 * 0.8, 480 * 0.8));


    std::cout << "LSystem" << std::endl;
    engine.start();
}

void simpleTree2()
{
    std::string vertexShaderFilename("../src/shaders/vertex_shader.vert");
    std::string fragmentShaderFilename("../src/shaders/fragment_shader.frag");
    GraphicEngine engine;
    engine.init("logfile", vertexShaderFilename, fragmentShaderFilename);

    lsystem::Simulator simulator;
    lsystem::Symbols axiom;

    // Base branch
    lsystem::Symbol symbolBase("BaseBranch");
    symbolBase.addParameter("width", 4);

    // Lateral branch
    lsystem::Symbol symbolLateralBranch("LateralBranch");

    lsystem::Symbol symbolOffshoot("Offshoot");

    axiom.push_back(symbolBase);
    simulator.setAxiom(axiom);
    simulator.setStartPoint(glm::vec3(0, 0, 0));

    simulator.setHead(glm::vec3(0, 1, 0));
    simulator.setUp(glm::vec3(0, 0, -1));
    simulator.setLeft(glm::vec3(-1, 0, 0));
    simulator.setDeltaAngle(glm::quarter_pi< GLfloat > ());

    lsystem::VertexGenerator generator;
    generator.addDrawingFunction(symbolBase,
            [] (lsystem::VertexGenerator &g, lsystem::Symbol const &s)
            {
                GLfloat width = s["width"];
                for (int i = 0; i < width; ++i)
                {
                    g.drawLine();
                }
                //g.drawLine();
            });

    lsystem::Production productionS(symbolBase, 0.1,
            [=] (lsystem::Symbol const& s) -> lsystem::Symbols
            {
                lsystem::Symbols result;
                lsystem::Symbol tmp(s);
                auto& s_width = tmp["width"];
                if (s_width - 1 > 0)
                {
                    s_width -= 1;
                }

                result.push_back(symbolBase);
                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolYawLeft);
                result.push_back(tmp);
                result.push_back(symbolBase);
                result.push_back(symbolLateralBranch);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolYawRight);
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolRollRight);
                //result.push_back(lsystem::symbolRollRight);
                result.push_back(symbolBase);

                return result;
            });
    simulator.addProduction(productionS);

    generator.addDrawingFunction(symbolLateralBranch,
            [] (lsystem::VertexGenerator &g, lsystem::Symbol const &s)
            {
                g.saveDrawState();
                g.pitchUp();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.pitchUp();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.yawLeft();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.yawRight();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.rollLeft();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.rollRight();
                g.drawLine();
                g.restoreDrawState();
            });

    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::radians(34.0));
    simulator.setStartAngle(glm::half_pi< GLfloat >());

    simulator.setStepCount(3);
    engine.addGraphicObject(
            simulator.getGraphicObject(generator, 640 * 0.8, 480 * 0.8));


    std::cout << "LSystem" << std::endl;
    engine.start();
}

void simpleTree3()
{
    std::string vertexShaderFilename("../src/shaders/vertex_shader.vert");
    std::string fragmentShaderFilename("../src/shaders/fragment_shader.frag");
    GraphicEngine engine;
    engine.init("logfile", vertexShaderFilename, fragmentShaderFilename);

    lsystem::Simulator simulator;
    lsystem::Symbols axiom;

    // Base branch
    lsystem::Symbol symbolBase("BaseBranch");
    symbolBase.addParameter("width", 4);

    // Lateral branch
    lsystem::Symbol symbolLateralBranch("LateralBranch");

    lsystem::Symbol symbolOffshoot("Offshoot");

    axiom.push_back(symbolBase);
    simulator.setAxiom(axiom);
    simulator.setStartPoint(glm::vec3(0, 0, 0));

    simulator.setHead(glm::vec3(0, 1, 0));
    simulator.setUp(glm::vec3(0, 0, -1));
    simulator.setLeft(glm::vec3(-1, 0, 0));
    simulator.setDeltaAngle(glm::quarter_pi< GLfloat > ());

    lsystem::VertexGenerator generator;
    generator.addDrawingFunction(symbolBase,
            [] (lsystem::VertexGenerator &g, lsystem::Symbol const &s)
            {
                GLfloat width = s["width"];
                for (int i = 0; i < width; ++i)
                {
                    g.drawLine();
                }
                //g.drawLine();
            });

    lsystem::Production productionS(symbolBase, 0.1,
            [=] (lsystem::Symbol const& s) -> lsystem::Symbols
            {
                lsystem::Symbols result;
                lsystem::Symbol tmp(s);
                auto& s_width = tmp["width"];
                if (s_width - 1 > 0)
                {
                    s_width -= 1;
                }

                result.push_back(symbolBase);
                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolYawLeft);
                result.push_back(tmp);
                result.push_back(symbolLateralBranch);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolYawRight);
                result.push_back(tmp);
                result.push_back(symbolLateralBranch);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolPitchDown);
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolPitchUp);
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                //result.push_back(lsystem::symbolRollRight);
                //result.push_back(lsystem::symbolRollRight);
                result.push_back(symbolBase);

                return result;
            });
    simulator.addProduction(productionS);

    generator.addDrawingFunction(symbolLateralBranch,
            [] (lsystem::VertexGenerator &g, lsystem::Symbol const &s)
            {
                g.saveDrawState();
                g.pitchUp();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.pitchUp();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.yawLeft();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.yawRight();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.rollLeft();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.rollRight();
                g.drawLine();
                g.restoreDrawState();
            });

    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::radians(37.0));
    simulator.setStartAngle(glm::half_pi< GLfloat >());

    simulator.setStepCount(3);
    engine.addGraphicObject(
            simulator.getGraphicObject(generator, 640 * 0.8, 480 * 0.8));


    std::cout << "LSystem" << std::endl;
    engine.start();
}*/

void simpleTree1b()
{
    std::string vertexShaderFilename("../src/shaders/vertex_shader.vert");
    std::string fragmentShaderFilename("../src/shaders/fragment_shader.frag");
    GraphicEngine engine;
    engine.init("logfile", vertexShaderFilename, fragmentShaderFilename);

    lsystem::Simulator &simulator = lsystem::Simulator::getInstance();
    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setHead(glm::vec3(0, 1, 0));
    simulator.setUp(glm::vec3(0, 0, -1));
    simulator.setLeft(glm::vec3(-1, 0, 0));

    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::radians(20.0));
    simulator.setStartAngle(glm::half_pi< GLfloat >());

    lsystem::VertexGenerator &generator = lsystem::VertexGenerator::getInstance();

    // Offspring
    lsystem::Symbol symbolF =
        lsystem::SymbolBuilder::getBuilder()
        .setDrawingFunction(
            [&] (lsystem::Symbol const &)
            {
                generator.drawLine();
            })
        .setProduction(
            [=] (lsystem::Symbol const &s) -> lsystem::Symbols
            {
                lsystem::Symbol tmp(s);
                lsystem::Symbols result;
                result.push_back(tmp);
                result.push_back(tmp);
                return result;
            })
        .build();

    // Main symbol
    lsystem::Symbol symbolX =
        lsystem::SymbolBuilder::getBuilder()
        .setDrawingFunction(
            [&] (lsystem::Symbol const &)
            {
                generator.drawLine();

            })
        .setProduction(
            [=] (lsystem::Symbol const &s) -> lsystem::Symbols
            {
                lsystem::Symbol tmp(s);
                lsystem::Symbols result;

                result.push_back(symbolF);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::getSymbolYawLeft(
                            glm::radians(20.0),
                            [](double param) -> double
                            {
                                return param * 0.85;
                            }, 0.8)
                        );
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::getSymbolPitchUp(
                            glm::radians(20.0),
                            [](double param) -> double
                            {
                                return param * 0.95;
                            }, 0.8)
                        );
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(symbolF);
                result.push_back(lsystem::symbolSaveState);
                result.push_back(
                        lsystem::getSymbolYawRight(glm::radians(20.0), 0.0, 0.7));
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolPitchDown);
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolYawLeft);
                result.push_back(tmp);
                return result;
            }, 0.95)
        .build();

    lsystem::Symbols axiom;
    axiom.push_back(symbolX);
    simulator.setAxiom(axiom);

    simulator.setStepCount(4);
    engine.addGraphicObject(
            simulator.getGraphicObject());


    std::cout << "LSystem" << std::endl;
    engine.start();
}

void simpleTree2b()
{
    std::string vertexShaderFilename("../src/shaders/vertex_shader.vert");
    std::string fragmentShaderFilename("../src/shaders/fragment_shader.frag");
    GraphicEngine engine;
    engine.init("logfile", vertexShaderFilename, fragmentShaderFilename);

    lsystem::Simulator &simulator = lsystem::Simulator::getInstance();
    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setHead(glm::vec3(0, 1, 0));
    simulator.setUp(glm::vec3(0, 0, -1));
    simulator.setLeft(glm::vec3(-1, 0, 0));

    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::radians(20.0));
    simulator.setStartAngle(glm::half_pi< GLfloat >());

    lsystem::VertexGenerator &generator = lsystem::VertexGenerator::getInstance();

    // Offspring
    lsystem::Symbol symbolF =
        lsystem::SymbolBuilder::getBuilder()
        .setDrawingFunction(
            [&] (lsystem::Symbol const &)
            {
                generator.drawLine();
            })
        .setProduction(
            [=] (lsystem::Symbol const &s) -> lsystem::Symbols
            {
                lsystem::Symbol tmp(s);
                lsystem::Symbols result;
                result.push_back(tmp);
                result.push_back(tmp);
                return result;
            })
        .build();

    // Main symbol
    lsystem::Symbol symbolX =
        lsystem::SymbolBuilder::getBuilder()
        .setDrawingFunction(
            [&] (lsystem::Symbol const &)
            {
                generator.drawLine();

            })
        .setProduction(
            [=] (lsystem::Symbol const &s) -> lsystem::Symbols
            {
                lsystem::Symbol tmp(s);
                lsystem::Symbols result;

                result.push_back(symbolF);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolYawLeft);
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolPitchUp);
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(symbolF);
                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolYawRight);
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolPitchDown);
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolYawLeft);
                result.push_back(tmp);
                return result;
            })
        .build();

    lsystem::Symbols axiom;
    axiom.push_back(symbolX);
    simulator.setAxiom(axiom);

    simulator.setStepCount(4);
    engine.addGraphicObject(
            simulator.getGraphicObject());


    std::cout << "LSystem" << std::endl;
    engine.start();
}

void simpleTree3b()
{
    std::string vertexShaderFilename("../src/shaders/vertex_shader.vert");
    std::string fragmentShaderFilename("../src/shaders/fragment_shader.frag");
    GraphicEngine engine;
    engine.init("logfile", vertexShaderFilename, fragmentShaderFilename);

    lsystem::Simulator &simulator = lsystem::Simulator::getInstance();
    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setHead(glm::vec3(0, 1, 0));
    simulator.setUp(glm::vec3(0, 0, -1));
    simulator.setLeft(glm::vec3(-1, 0, 0));
    simulator.setDeltaAngle(glm::quarter_pi< GLfloat > ());


    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::radians(37.0));
    simulator.setStartAngle(glm::half_pi< GLfloat >());

    lsystem::VertexGenerator &generator = lsystem::VertexGenerator::getInstance();

    // Lateral branch
    lsystem::Symbol symbolLateralBranch =
        lsystem::SymbolBuilder::getBuilder()
        .setDrawingFunction(
            [] (lsystem::Symbol const &)
            {
                lsystem::VertexGenerator &g
                    = lsystem::VertexGenerator::getInstance();
                g.saveDrawState();
                g.pitchUp();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.pitchUp();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.yawLeft();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.yawRight();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.rollLeft();
                g.drawLine();
                g.restoreDrawState();

                g.saveDrawState();
                g.rollRight();
                g.drawLine();
                g.restoreDrawState();
            })
        .build();

    // Base branch
    lsystem::Symbol symbolBase =
        lsystem::SymbolBuilder::getBuilder()
        .addParameter("width", 4)
        .setDrawingFunction(
            [] (lsystem::Symbol const &s)
            {
                lsystem::VertexGenerator &g
                    = lsystem::VertexGenerator::getInstance();
                GLfloat width = s["width"];
                for (int i = 0; i < width; ++i)
                {
                    g.drawLine();
                }
                //g.drawLine();
            })
        .setProduction(
            [=] (lsystem::Symbol const& s) -> lsystem::Symbols
            {
                lsystem::Symbols result;
                lsystem::Symbol tmp(s);

                auto& s_width = tmp["width"];
                if (s_width - 1 > 0)
                {
                    s_width -= 1;
                }

                result.push_back(s);
                result.push_back(lsystem::symbolSaveState);
                //result.push_back(lsystem::symbolYawLeft);
                result.push_back(lsystem::getSymbolYawRight(
                      glm::radians(glm::half_pi< GLfloat >())
                    , glm::radians(glm::quarter_pi< GLfloat>() / 4.0)));
                result.push_back(tmp);
                result.push_back(symbolLateralBranch);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolYawRight);
                result.push_back(tmp);
                result.push_back(symbolLateralBranch);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolPitchDown);
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                result.push_back(lsystem::symbolSaveState);
                result.push_back(lsystem::symbolPitchUp);
                result.push_back(tmp);
                result.push_back(lsystem::symbolRestoreState);

                //result.push_back(lsystem::symbolRollRight);
                //result.push_back(lsystem::symbolRollRight);
                result.push_back(s);

                return result;
            })
        .build();

    /* 
    // Offshoot branch
    lsystem::Symbol symbolOffshoot =
        lsystem::SymbolBuilder::getBuilder(generator, simulator)
        .build();
        */

    lsystem::Symbols axiom;
    axiom.push_back(symbolBase);
    simulator.setAxiom(axiom);

    simulator.setStepCount(4);
    engine.addGraphicObject(
            simulator.getGraphicObject());


    std::cout << "LSystem" << std::endl;
    engine.start();
}

int main()
{
    simpleTree1b();
    //simpleTree2b();
    //simpleTree3b();
    return 0;
}
