#ifndef LSYSTEM_SIMULATOR
#define LSYSTEM_SIMULATOR

#include <iostream>
#include <unordered_map>
#include <tuple>

#include "generator.hpp"

namespace lsystem
{
    typedef std::unordered_map< char, std::string > CharacterTransitionMap;

    class Simulator
    {
        public:
            Simulator();

            void setAxiom(std::string const &axiom);

            void addProduction(char character, std::string const &production);

            void clearProdutions();

            void addCommand(char character, std::string const &command);

            void clearCommands();

            void setStepCount(std::size_t stepCount);

            void setStartAngle(GLfloat angle);
           
            void setDeltaAngle(GLfloat angle);

            void setStartPoint(glm::vec3 startPoint);

            GraphicObjectPtr getGraphicObject();

        private:
            void simulate(); 

            std::string mapString(CharacterTransitionMap const &map);

        private:
            std::string processedString;
            CharacterTransitionMap productions;
            CharacterTransitionMap commands;
            std::size_t stepCount;
            GLfloat startAngle;
            GLfloat deltaAngle;
            glm::vec3 startPoint;
    };
}

#endif