#ifndef GRAPHIC_OBJECT_HPP
#define GRAPHIC_OBJECT_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>

#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
};

class GraphicObject
{
        glm::vec3 position;
        std::vector< GLfloat > vertices;
        GLenum drawMode;

    public:
        GraphicObject()
            : position(0, 0, 0)
            , drawMode(GL_LINES)
        {
        }

        void addVertex(Vertex const &vertex)
        {
            vertices.push_back(vertex.position.x);
            vertices.push_back(vertex.position.y);
            vertices.push_back(vertex.position.z);
            vertices.push_back(vertex.color.r);
            vertices.push_back(vertex.color.g);
            vertices.push_back(vertex.color.b);
        }

        std::size_t getVertexCount() const
        {
            return vertices.size();
        }

        GLfloat const *getRawPointer()
        {
            return &vertices[0];
        }
};

#endif
