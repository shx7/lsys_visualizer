#ifndef GRAPHIC_OBJECT_HPP
#define GRAPHIC_OBJECT_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <list>

class Vertex
{
    glm::vec3 position;
    glm::vec3 color;
};

class GraphicObject
{
    glm::vec3 position;
    std::list< Vertex > vertices;
};

#endif
