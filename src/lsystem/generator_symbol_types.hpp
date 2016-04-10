#ifndef GENERATOR_SYMBOL_TYPES
#define GENERATOR_SYMBOL_TYPES

#include "grammar_util.hpp"

namespace lsystem
{ 
    static const Symbol symbolDrawLine("F");
    static const Symbol symbolDrawSpace("f");
    static const Symbol symbolRotateRight("+");
    static const Symbol symbolRotateLeft("-");
    static const Symbol symbolSaveState("[");
    static const Symbol symbolRestoreState("]");
} // lsystem

#endif
