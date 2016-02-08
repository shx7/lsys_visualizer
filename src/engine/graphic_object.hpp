#ifndef GRAPHIC_OBJECT_HPP
#define GRAPHIC_OBJECT_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>

#include <vector>
#include <memory>

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
        GLuint vaoIndex;
        bool isVAOIndexSet;

    public:
        GraphicObject()
            : position(0, 0, 0)
            , drawMode(GL_LINES)
            , vaoIndex(0)
            , isVAOIndexSet(false)
        {
        }

        void addVertex(glm::vec4 const &position, glm::vec3 const &color)
        {
            vertices.push_back(position.x);
            vertices.push_back(position.y);
            vertices.push_back(position.z);
            vertices.push_back(position.w);
            vertices.push_back(color.r);
            vertices.push_back(color.g);
            vertices.push_back(color.b);
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

        GLfloat const *getRawPointer() const
        {
            return vertices.data();
        }

        void setVAOIdentifier(GLuint vaoId)
        {
            isVAOIndexSet = true;
            vaoIndex = vaoId;
        }

        GLuint getVAOIdentifier()
        {
            if (!isVAOIndexSet)
            {
                throw std::runtime_error("VAO index not set for GraphicObject");
            }
            return vaoIndex;
        }

        GLenum getDrawMode() const
        {
            return drawMode;
        }

        void setDrawMode(GLenum mode)
        {
            drawMode = mode;
        }
}; 

typedef std::shared_ptr< GraphicObject > GraphicObjectPtr;

#endif
