/************************************************
 *
 * lsystem::Simulator contains implementation
 * of deterministic/stochastic LSystem algorithm.
 *
 * Simulator contains properties such as:
 * 1) Axiom - starting string, from wich all
 * productions runs.
 *
 * 2) Productions - pairs of (char, string) for
 * replacing on every simulation round.
 * Productions also have probabilities (for
 * stochastic productions), by default all
 * productions are deterministic.
 *
 * 3) Commands binded to every symbol of aphabet.
 * Commands define character commands for
 * turtle-interpretation of processed string.
 * Supported symbols:
 *     F draw stew
 *     f draw space
 *     + turn by clockwise
 *     - turn by counter-clockwise
 *
 * After simulation Simulator produces
 * GraphicObject for representing by Engine
 ***********************************************/

#ifndef LSYSTEM_SIMULATOR
#define LSYSTEM_SIMULATOR

#include <random>

#include <iostream>
#include <unordered_map>
#include <vector>
#include <tuple>

#include "generator.hpp"

namespace lsystem
{
    struct Parameter
    {
        std::string name = "";
        GLfloat value = 0;

        Parameter(std::string const &name, GLfloat value)
            : name(name)
            , value(value)
        {}
    };

    struct Symbol
    {
        std::string value;
        std::vector< Parameter > parameters;

        Symbol(std::string const &value)
            : value(value)
        {}

        void addParameter(Parameter const &param)
        {
            parameters.push_back(param);
        }
    };

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
                , distribution(0.0, 1.0)
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

            void generateCommandsString(); 

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
