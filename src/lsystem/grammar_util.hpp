#ifndef GRAMMAR_UTIL_HPP
#define GRAMMAR_UTIL_HPP

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
}; // lsystem

#endif
