#ifndef GRAMMAR_UTIL_HPP
#define GRAMMAR_UTIL_HPP

#include <map>

namespace lsystem
{
    typedef char Command;
    typedef std::vector< Command > Commands;
    typedef std::shared_ptr< Commands > CommandsPtr;

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
        std::string name;
        std::vector< Parameter > parameters;
        CommandsPtr drawCommands;

        Symbol(std::string const &name)
            : name(name)
        {}

        void addParameter(Parameter const &param)
        {
            parameters.push_back(param);
        }
    };

    typedef std::vector< Symbol > Symbols; 

    typedef Symbols (*ProducingFunction)(Symbol const &symbol);

    struct Production
    {
        std::string symbolName;
        double probability;
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

        void appendProductionResult(
                  Symbol const &symbol
                , Symbols &result)
        {
            auto tmp = producingFunction(symbol);
            result.insert(result.end(), tmp.begin(), tmp.end());
        }

        bool operator<(Production const &production) const
        {
            return symbolName < production.symbolName;
        }
    };

    typedef std::map< std::string, Production > Productions;
}; // lsystem

#endif
