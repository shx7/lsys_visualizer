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
        std::map< std::string, GLfloat > parameters;
        CommandsPtr drawCommands;

        Symbol(std::string const &name)
            : name(name)
            , drawCommands(new Commands)
        {}

        void addParameter(std::string const &name, GLfloat value)
        {
            parameters.insert(std::make_pair(name, value));
        }

        void addCommand(Command cmd)
        {
            drawCommands->push_back(cmd);
        }
    };

    typedef std::vector< Symbol > Symbols; 

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
            return producingSymbol.name < production.producingSymbol.name;
        }
    };

    typedef std::map< std::string, Production > Productions;
}; // lsystem

#endif
