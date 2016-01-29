#include <iostream>
#include "engine.hpp"

int main()
{
    GraphicEngine engine("logfile", "vertex_shader.vert", "fragment_shader.frag");
    std::cout << "LSystem" << std::endl;
    return 0;
}
