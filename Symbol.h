#pragma once

enum class SymbolColor
{
    Green,
    Blue,
    Cyan,
    Red,
    Magenta,
    Yellow,
    White
};

class Symbol
{
public:
    Symbol(char value, SymbolColor color);

    char getValue() const;
    SymbolColor getColor() const;

private:
    char symbolValue;
    SymbolColor symbolColor;
};