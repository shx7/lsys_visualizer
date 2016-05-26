#ifndef GENERATOR_SYMBOL_TYPES
#define GENERATOR_SYMBOL_TYPES

#include "symbol.hpp"

namespace lsystem
{
    static const Symbol symbolDrawLine("F");
    static const Symbol symbolDrawSpace("f");
    static const Symbol symbolYawRight("+");
    static const Symbol symbolYawLeft("-");
    static const Symbol symbolPitchDown("&");
    static const Symbol symbolPitchUp("^");
    static const Symbol symbolRollLeft("\\");
    static const Symbol symbolRollRight("/");
    static const Symbol symbolSaveState("[");
    static const Symbol symbolRestoreState("]");
} // lsystem

#endif
