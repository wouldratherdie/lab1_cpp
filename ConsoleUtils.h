#pragma once

#include "Symbol.h"

class ConsoleUtils
{
public:
    static bool setCursorPosition(int x, int y);
    static bool setTextColor(SymbolColor color);
    static bool clearScreen();
    static bool setCursorVisible(bool visible);
    static bool getWindowSize(int& width, int& height);
    static bool drawSymbol(int x, int y, const Symbol& symbol);
    static bool eraseCharacter(int x, int y);
};