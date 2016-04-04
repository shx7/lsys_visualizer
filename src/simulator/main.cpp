#include <iostream>
#include "engine.hpp"
#include "generator.hpp"
#include "simulator.hpp"
#include "grammar_util.hpp"

#include "glm/gtc/constants.hpp"

int main()
{
    std::string vertexShaderFilename("../src/shaders/vertex_shader.vert");
    std::string fragmentShaderFilename("../src/shaders/fragment_shader.frag");
    GraphicEngine engine;
    engine.init("logfile", vertexShaderFilename, fragmentShaderFilename);

    // Test for lsystem::VertexGenerator
    /*lsystem::VertexGenerator vertexGenerator;
    vertexGenerator.setDrawState(std::make_tuple(glm::vec3(0, 0, 0), 0, 3.14 / 4));
    vertexGenerator.setCommandsString("F-F+FF-F+FF-F+FF-F+F");
    GraphicObjectPtr obj1 = vertexGenerator.generateGraphicObject(); 
    engine.addGraphicObject(obj1);*/
    

    // Test for GraphicEngine
    /*GraphicObjectPtr obj1(new GraphicObject);
    obj1->addVertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    obj1->addVertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    obj1->addVertex(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    obj1->setDrawMode(GL_TRIANGLES);
    engine.addGraphicObject(obj1);*/

    // Test for LSystem generator
    /*lsystem::Simulator simulator;
    simulator.setAxiom("F-F-F-F");
    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::half_pi< GLfloat > ());
    simulator.setStartAngle(0);

    simulator.addProduction('F', "FF-F-F-F-F-F+F");
    simulator.addProduction('+', "+");
    simulator.addProduction('-', "-");
    simulator.addProduction('f', "f");

    simulator.addCommand('F', "F");
    simulator.addCommand('+', "+");
    simulator.addCommand('-', "-");
    simulator.addCommand('f', "f");

    simulator.setStepCount(3);
    engine.addGraphicObject(simulator.getGraphicObject());*/

    // Test for tree LSystem
    /*lsystem::Simulator simulator;
    simulator.setAxiom("F");
    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::quarter_pi< GLfloat > ());
    simulator.setStartAngle(glm::half_pi< GLfloat >());

    simulator.addProduction('F', "F[+F]F[-FF]F");
    simulator.addProduction('+', "+");
    simulator.addProduction('-', "-");
    simulator.addProduction('[', "[");
    simulator.addProduction(']', "]");

    simulator.addCommand('F', "F");
    simulator.addCommand('+', "+");
    simulator.addCommand('-', "-");
    simulator.addCommand('[', "[");
    simulator.addCommand(']', "]");

    simulator.setStepCount(4);
    engine.addGraphicObject(simulator.getGraphicObject(400, 400));*/

    // Test for SLSystem
    /*lsystem::Simulator simulator;
    simulator.setAxiom("SS");
    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::quarter_pi< GLfloat > ());
    simulator.setStartAngle(glm::half_pi< GLfloat >());

    simulator.addProduction('S', "SLSRS", 0.98);
    simulator.addProduction('L', "[+SLS-SRS]", 0.75);
    simulator.addProduction('R', "[-SLSSRS]", 0.85);
    simulator.addProduction('+', "+");
    simulator.addProduction('-', "-");
    simulator.addProduction('[', "[");
    simulator.addProduction(']', "]");

    simulator.addCommand('S', "F");
    simulator.addCommand('L', "[+F]");
    simulator.addCommand('R', "[-FF]");
    simulator.addCommand('+', "+");
    simulator.addCommand('-', "-");
    simulator.addCommand('[', "[");
    simulator.addCommand(']', "]");*/

    /*simulator.setAxiom("F");
    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::quarter_pi< GLfloat > ());
    simulator.setStartAngle(glm::half_pi< GLfloat >());

    simulator.addProduction('F', "F[+F]F[-F]F");
    simulator.addProduction('+', "+");
    simulator.addProduction('-', "-");
    simulator.addProduction('[', "[");
    simulator.addProduction(']', "]");

    simulator.addCommand('F', "F");
    simulator.addCommand('+', "+");
    simulator.addCommand('-', "-");
    simulator.addCommand('[', "[");
    simulator.addCommand(']', "]");*/


    // Test for P LSystem
    lsystem::Simulator simulator;
    lsystem::Symbols axiom;
    lsystem::Symbol symbolS("S");
    //symbolS.addCommand('F');
    symbolS.addParameter("width", 0);
    //symbolS.addCommand('f');
    //symbolS.addCommand('+');
    axiom.push_back(symbolS);
    axiom.push_back(symbolS);
    simulator.setAxiom(axiom);

    lsystem::VertexGenerator generator;
    generator.addDrawingFunction(symbolS,
            [] (lsystem::VertexGenerator &g)
            {
                g.drawLine();
                g.rotateRight();
            });

    lsystem::Production productionS(symbolS, 0.1,
            [] (lsystem::Symbol const& s) -> lsystem::Symbols
            {
                lsystem::Symbols result;
                lsystem::Symbol tmp(s);
                auto& s_width = tmp["width"];
                s_width += 1;
                result.push_back(tmp);
                result.push_back(s);
                return result;
            });
    simulator.addProduction(productionS);
    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::quarter_pi< GLfloat > ());
    simulator.setStartAngle(glm::half_pi< GLfloat >());

    simulator.setStepCount(10);
    engine.addGraphicObject(
            simulator.getGraphicObject(generator, 640 * 0.8, 480 * 0.8));


    std::cout << "LSystem" << std::endl;
    engine.start();
    return 0;
}
