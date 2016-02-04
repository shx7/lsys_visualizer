#ifndef LSYSTEM_SIMULATOR
#define LSYSTEM_SIMULATOR

#include <random>

#include <iostream>
#include <unordered_map>
#include <tuple>

#include "generator.hpp"

namespace lsystem
{
    struct Production
    {
        char producing_character;
        std::string production_string;
        double probability;

        Production(char producing_character
                , std::string const &production_string
                , double probability)
            : producing_character(producing_character)
            , production_string(production_string)
            , probability(probability) {}
    };

    typedef std::unordered_map< char, Production > ProductionMap; 
    typedef std::unordered_map< char, std::string > CharacterTransitionMap; 

    class RandomGenerator
    {
        public:
            RandomGenerator()
                : randomGenerator(randomDevice())
            {
            }

            double getNextRandom()
            {
                return distribution(randomGenerator);
            }

        private:
            std::random_device randomDevice;
            std::mt19937 randomGenerator;
            std::uniform_real_distribution< double > distribution;
    };

    class Simulator
    {
        public:
            Simulator();

            void setAxiom(std::string const &axiom);

            void addProduction(char producing_character
                    , std::string const &production_string
                    , double probability = 1.0);

            void clearProdutions();

            void addCommand(char producing_character, std::string const &command);

            void clearCommands();

            void setStepCount(std::size_t stepCount);

            void setStartAngle(GLfloat angle);
           
            void setDeltaAngle(GLfloat angle);

            void setStartPoint(glm::vec3 startPoint);

            GraphicObjectPtr getGraphicObject(
                      GLfloat imageWidth
                    , GLfloat imageHeight);

        private:
            void simulate(); 

            std::string mapString(CharacterTransitionMap const &map);

            std::string applyProductions(ProductionMap const &map);

        private:
            std::string processedString;
            ProductionMap productions;
            CharacterTransitionMap commands;

            std::size_t stepCount;
            GLfloat startAngle;
            GLfloat deltaAngle;
            glm::vec3 startPoint;

            RandomGenerator randomGenerator;
    };
}

#endif
