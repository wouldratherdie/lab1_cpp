#pragma once

#include "Symbol.h"

// Provides utility functions for Windows console operations.
class ConsoleUtils
{
public:
    // Changes the cursor position.
    static bool setCursorPosition(int x, int y);

    // Changes the console text color.
    static bool setTextColor(SymbolColor color);

    // Clears the console screen.
    static bool clearScreen();

    // Changes cursor visibility.
    static bool setCursorVisible(bool visible);

    // Returns the visible console dimensions.
    static bool getWindowSize(int& width, int& height);

    // Draws a symbol at the specified position.
    static bool drawSymbol(int x, int y, const Symbol& symbol);

    // Erases a character at the specified position.
    static bool eraseCharacter(int x, int y);
};