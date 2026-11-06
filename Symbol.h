#pragma once

// Defines available symbol colors.
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

// Represents a single Matrix symbol.
class Symbol
{
public:
    // Initializes a symbol with its value and color.
    Symbol(char value, SymbolColor color);

    // Returns the symbol character.
    char getValue() const;

    // Returns the symbol color.
    SymbolColor getColor() const;

private:
    char symbolValue;
    SymbolColor symbolColor;
};