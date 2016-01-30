#include <iostream>
#include "engine.hpp"

int main()
{
    std::string vertexShaderFilename("../src/shaders/vertex_shader.vert");
    std::string fragmentShaderFilename("../src/shaders/fragment_shader.frag");
    GraphicEngine engine;
    engine.init("logfile", vertexShaderFilename, fragmentShaderFilename);

    std::cout << "LSystem" << std::endl;
    engine.start();
    return 0;
}
