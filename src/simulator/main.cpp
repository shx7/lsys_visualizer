#include <iostream>
#include "engine.hpp"

int main()
{
    std::string vertexShaderFilename("../src/shaders/vertex_shader.vert");
    std::string fragmentShaderFilename("../src/shaders/fragment_shader.frag");
    GraphicEngine engine;
    engine.init("logfile", vertexShaderFilename, fragmentShaderFilename);

    GraphicObjectPtr obj1(new GraphicObject);
    obj1->addVertex(glm::vec3(0.1, 0, 0), glm::vec3(0.5, 0.5, 0.9));
    obj1->addVertex(glm::vec3(0.5, 0.5, 0), glm::vec3(0.5, 0.0, 0.9));
    obj1->addVertex(glm::vec3(0.7, 0.7, 0), glm::vec3(0.5, 0.0, 0.9));
    /*obj1->addVertex(glm::vec3(0.5, 0.5, 0), glm::vec3(0, 0.2, 1));
    obj1->addVertex(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));*/
    obj1->setDrawMode(GL_LINE_STRIP);

    engine.addGraphicObject(obj1);

    std::cout << "LSystem" << std::endl;
    engine.start();
    return 0;
}
