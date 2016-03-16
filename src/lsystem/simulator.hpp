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
#include "grammar_util.hpp"

namespace lsystem
{
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
            // TODO: think about set for productions
            Productions productions;
            Symbols axiom; 
    };
}

#endif
