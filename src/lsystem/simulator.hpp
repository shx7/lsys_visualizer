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

    typedef std::vector< Symbol > Symbols; 

    typedef void (*ProducingFunction)(
              Symbol const &symbol
            , Symbols const &productionSymbols);

    struct Production
    {
        std::string symbolName;
        double probability;
        Symbols productionSymbols;
        ProducingFunction producingFunction;

        Production(
                  std::string const &symbolName
                , double probability)
            : symbolName(symbolName)
            , probability(probability)
        {}

        void setProductionFunctoin(
                ProducingFunction const &function)
        {
            producingFunction = function;
        }
    };

    typedef std::vector< Production > Productions;

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

            void setAxiom(Symbols const &axiom);

            void addProduction(Production const &production);

            void clearProdutions();

            void setStepCount(std::size_t stepCount);

            void setStartAngle(GLfloat angle);
           
            void setDeltaAngle(GLfloat angle);

            void setStartPoint(glm::vec3 startPoint);

            GraphicObjectPtr getGraphicObject(
                      GLfloat imageWidth
                    , GLfloat imageHeight);

        private: 
            CommandsPtr generateCommands();

            void applyProductions(Symbols &symbols);

            CommandsPtr symbolsToCommands(Symbols const &symbols);

        private: 
            std::size_t stepCount;
            GLfloat startAngle;
            GLfloat deltaAngle;
            glm::vec3 startPoint;

            RandomGenerator randomGenerator;
            Productions productions;
            Symbols axiom; 
    };
}

#endif
