#include "grammar_util.hpp"

using namespace lsystem;

RandomGenerator::
RandomGenerator()
    : randomGenerator(randomDevice())
    , distribution(0.0, 1.0)
{
}

double
RandomGenerator::
getNextRandom()
{
    return distribution(randomGenerator);
}
