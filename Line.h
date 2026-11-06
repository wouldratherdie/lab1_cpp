#pragma once

#include "Symbol.h"

class Line
{
public:
    Line(int initialX, int requestedLength,
        int windowHeight, SymbolColor initialColor);

    void advance();
    bool isFinished() const;

private:
    static char generateRandomCharacter();

    int xPosition;
    int lineLength;
    int consoleHeight;
    int currentY;

    SymbolColor lineColor;
    bool finished;
};