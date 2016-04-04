#ifndef GRAMMAR_UTIL_HPP
#define GRAMMAR_UTIL_HPP

#include <map>
#include <memory>

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

        Symbol(std::string const &name)
            : name(name)
        {}

        Symbol(Symbol const &s)
        {
            name = s.name;
            parameters = s.parameters;
        }

        GLfloat &operator[](std::string const &parameter_name)
        {
            auto it = parameters.find(parameter_name);
            if (it == parameters.end())
            {
                throw std::runtime_error(
                    "Access to non-existent parameter '" + parameter_name + "'");
            }
            return it->second;
        }

        void addParameter(std::string const &name, GLfloat value)
        {
            parameters.insert(std::make_pair(name, value));
        }

        bool operator<(Symbol const &s) const
        {
            return name < s.name;
        }
    };

    typedef std::vector< Symbol > Symbols; 
    typedef std::shared_ptr< Symbols > SymbolsPtr;

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
