#pragma once

#include "Symbol.h"

// Represents a vertical moving line.
class Line
{
public:
    // Creates a line with the specified parameters.
    Line(int initialX, int requestedLength,
        int windowHeight, SymbolColor initialColor);

    // Performs one movement step.
    void advance();

    // Checks whether the line has left the screen.
    bool isFinished() const;

private:
    // Generates a random printable character.
    static char generateRandomCharacter();

    int xPosition;
    int lineLength;
    int consoleHeight;
    int currentY;

    SymbolColor lineColor;
    bool finished;
};