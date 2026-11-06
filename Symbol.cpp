#include "Symbol.h"

Symbol::Symbol(char value, SymbolColor color)
    : symbolValue(value), symbolColor(color)
{}

char Symbol::getValue() const
{
    return symbolValue;
}

SymbolColor Symbol::getColor() const
{
    return symbolColor;
}