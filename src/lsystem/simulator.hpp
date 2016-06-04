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

#include <iostream>
#include <unordered_map>
#include <vector>
#include <tuple>

#include "generator.hpp"
#include "grammar_util.hpp"

namespace lsystem
{
    class Simulator
    {
        public:
            static Simulator &getInstance();

            void setAxiom(Symbols const &axiom);

            void addProduction(Production const &production);

            void clearProdutions();

            void setStepCount(std::size_t stepCount);

            void setStartAngle(GLfloat angle);
           
            void setDeltaAngle(GLfloat angle);

            void setStartPoint(glm::vec3 startPoint);

            GraphicObjectPtr getGraphicObject();

            void setUp(glm::vec3 const &up);

            void setHead(glm::vec3 const &head);

            void setLeft(glm::vec3 const &left);

        private: 
            Simulator();

            SymbolsPtr generateSymbolsSequence();

            void applyProductions(Symbols &symbols);

        private: 
            std::size_t stepCount;
            GLfloat startAngle;
            GLfloat deltaAngle;
            glm::vec3 startPoint;
            glm::vec3 up, head, left;

            // TODO: think about set for productions
            std::map< std::string, Production >productions;
            Symbols axiom; 

            static Simulator instance;
    };
}

#endif
