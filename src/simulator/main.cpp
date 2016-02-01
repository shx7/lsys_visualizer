#include <iostream>
#include "engine.hpp"

int main()
{
    std::string vertexShaderFilename("../src/shaders/vertex_shader.vert");
    std::string fragmentShaderFilename("../src/shaders/fragment_shader.frag");
    GraphicEngine engine;
    engine.init("logfile", vertexShaderFilename, fragmentShaderFilename);

    GraphicObjectPtr obj1(new GraphicObject);
    obj1->addVertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    obj1->addVertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    obj1->addVertex(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    obj1->setDrawMode(GL_TRIANGLES);

    engine.addGraphicObject(obj1);

    std::cout << "LSystem" << std::endl;
    engine.start();
    return 0;
}
