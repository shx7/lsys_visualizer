#ifndef GRAMMAR_UTIL_HPP
#define GRAMMAR_UTIL_HPP

#include <map>
#include <memory>

#include "symbol.hpp"

namespace lsystem
{
    typedef char Command;
    typedef std::vector< Command > Commands;
    typedef std::shared_ptr< Commands > CommandsPtr;

    //typedef Symbols (*ProducingFunction)(Symbol const &symbol);
    typedef std::function<Symbols (Symbol const &)> ProducingFunction;

    struct Production
    {
        Symbol producingSymbol;
        double probability;
        ProducingFunction producingFunction;

        Production(
                  Symbol const &producingSymbol
                , double probability
                , ProducingFunction const &function)
            : producingSymbol(producingSymbol)
            , probability(probability)
            , producingFunction(function)
        {}

        void appendProductionResult(
                  Symbol const &symbol
                , Symbols &result)
        {
            Symbols const &tmp = producingFunction(symbol);
            result.insert(result.end(), tmp.cbegin(), tmp.cend());
        }

        bool operator<(Production const &production) const
        {
            return producingSymbol.getName()
                < production.producingSymbol.getName();
        }
    };

    typedef std::map< std::string, Production > Productions;
}; // lsystem

#endif
