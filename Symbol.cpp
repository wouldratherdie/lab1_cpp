#include "Symbol.h"

Symbol::Symbol(char value, SymbolColor color)
    : value_(value), color_(color)
{}

char Symbol::getValue() const
{
    return value_;
}

SymbolColor Symbol::getColor() const
{
    return color_;
}