#ifndef GRAPHIC_OBJECT_HPP
#define GRAPHIC_OBJECT_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>

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
        GLenum drawMode;

    public:
        GraphicObject()
            : position(0, 0, 0)
            , drawMode(GL_LINES)
        {
        }

        void addVertex(Vertex const &vertex)
        {
            vertices.push_back(vertex);
        }
};

#endif
