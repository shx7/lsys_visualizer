#include <iostream>
#include "engine.hpp"
#include "generator.hpp"
#include "simulator.hpp"
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
    lsystem::Simulator simulator;
    simulator.setAxiom("S");
    simulator.setStartPoint(glm::vec3(0, 0, 0));
    simulator.setDeltaAngle(glm::quarter_pi< GLfloat > ());
    simulator.setStartAngle(glm::half_pi< GLfloat >());

    simulator.addProduction('S', "SLSRS");
    simulator.addProduction('L', "[+SLSRS]", 0.5);
    simulator.addProduction('R', "[-SLSRS]");
    simulator.addProduction('+', "+");
    simulator.addProduction('-', "-");
    simulator.addProduction('[', "[");
    simulator.addProduction(']', "]");

    simulator.addCommand('S', "F");
    simulator.addCommand('L', "[+F]");
    simulator.addCommand('R', "[-F]");
    simulator.addCommand('+', "+");
    simulator.addCommand('-', "-");
    simulator.addCommand('[', "[");
    simulator.addCommand(']', "]");

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

    simulator.setStepCount(4);
    engine.addGraphicObject(simulator.getGraphicObject(640 * 0.7, 480 * 0.7));


    std::cout << "LSystem" << std::endl;
    engine.start();
    return 0;
}
