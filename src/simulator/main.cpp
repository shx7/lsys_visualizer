#include <iostream>
#include "engine.hpp"

int main()
{
    std::string vertexShaderFilename("vertex_shader.vert");
    std::string fragmentShaderFilename("fragment_shader.frag");
    GraphicEngine engine("logfile", vertexShaderFilename, fragmentShaderFilename);
    std::cout << "LSystem" << std::endl;
    return 0;
}
