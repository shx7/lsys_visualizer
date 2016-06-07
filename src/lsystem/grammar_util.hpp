#ifndef GRAMMAR_UTIL_HPP
#define GRAMMAR_UTIL_HPP

#include <random> 

#include <map>
#include <memory>

#include "symbol.hpp"

namespace lsystem
{
    /**
     *  lsystem::RandomGenerator is responsible for generation
     *  random numbers, that is using in making decisions in Simulator
     *  about apllying stochastic productions.
     */
    class RandomGenerator
    {
        public:
            RandomGenerator();

            double getNextRandom();

        private:
            std::random_device randomDevice;
            std::mt19937 randomGenerator;
            std::uniform_real_distribution< double > distribution;
    };

    typedef char Command;
    typedef std::vector< Command > Commands;
    typedef std::shared_ptr< Commands > CommandsPtr;

    typedef std::function<Symbols (Symbol const &)> ProducingFunction;

    /**
     *  lsystem::Production represents symbol production in system.
     *  One Symbol can own only one Production to avoid ambiguity.
     *  Production can be made stochastic by adding probability value into
     *  ctor.
     */
    struct Production
    {
        static RandomGenerator randomGenerator;

        Symbol producingSymbol;
        double probability;
        ProducingFunction producingFunction;

        Production(
                  Symbol const &producingSymbol
                , double probability
                , ProducingFunction const &function);

        void appendProductionResult(
                  Symbol const &symbol
                , Symbols &result);

        bool operator<(Production const &production) const;
    };

    typedef std::map< std::string, Production > Productions;
}; // lsystem

#endif
