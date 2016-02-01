#include <iostream>
#include "engine.hpp"
#include "generator.hpp"
#include "simulator.hpp"

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
    lsystem::Simulator simulator;
    simulator.setAxiom("AB");
    simulator.setDeltaAngle(3.14159 / 4);

    simulator.addProduction('A', "A");
    simulator.addProduction('B', "BAB");

    simulator.addCommand('A', "F-");
    simulator.addCommand('B', "F+F");

    simulator.setStepCount(2);
    engine.addGraphicObject(simulator.getGraphicObject());


    std::cout << "LSystem" << std::endl;
    engine.start();
    return 0;
}
