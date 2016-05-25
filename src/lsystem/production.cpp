#include "grammar_util.hpp"

using namespace lsystem;

RandomGenerator Production::randomGenerator;

Production::
Production(
          Symbol const &producingSymbol
        , double probability
        , ProducingFunction const &function)
    : producingSymbol(producingSymbol)
    , probability(probability)
    , producingFunction(function)
{}

void
Production::
appendProductionResult(
          Symbol const &symbol
        , Symbols &result)
{
    bool flagApplyProduction = true;
    if (probability < 1.0)
    {
        flagApplyProduction
            = randomGenerator.getNextRandom() <= probability;
    }

    if (flagApplyProduction)
    {
        Symbols const &tmp = producingFunction(symbol);
        result.insert(result.end(), tmp.cbegin(), tmp.cend());
    }
}

bool
Production::
operator<(Production const &production) const
{
    return producingSymbol.getName()
        < production.producingSymbol.getName();
}
