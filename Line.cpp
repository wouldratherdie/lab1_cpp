#include "Line.h"
#include "ConsoleUtils.h"

#include <random>
#include <stdexcept>
#include <string>

// Initializes the line parameters.
Line::Line(int initialX, int requestedLength,
    int windowHeight, SymbolColor initialColor)
    : xPosition(initialX),
    lineLength(requestedLength),
    consoleHeight(windowHeight),
    currentY(-1),
    lineColor(initialColor),
    finished(false)
{
    if (initialX < 0 || requestedLength < 1 || windowHeight < 1)
        throw std::invalid_argument("Invalid line parameters");
}

char Line::generateRandomCharacter()
{
    static const std::string characters =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    static std::mt19937 generator(std::random_device{}());

    static std::uniform_int_distribution<std::size_t> distribution(
        0, characters.size() - 1
    );

    return characters[distribution(generator)];
}

void Line::advance()
{
    if (finished)
        return;

    ++currentY;

    if (currentY < consoleHeight)
    {
        Symbol symbol(generateRandomCharacter(), lineColor);

        if (!ConsoleUtils::drawSymbol(xPosition, currentY, symbol))
        {
            finished = true;
            return;
        }
    }

    const int tailY = currentY - lineLength;

    if (tailY >= 0 && tailY < consoleHeight)
    {
        if (!ConsoleUtils::eraseCharacter(xPosition, tailY))
        {
            finished = true;
            return;
        }
    }

    if (currentY >= consoleHeight + lineLength - 1)
        finished = true;
}

bool Line::isFinished() const
{
    return finished;
}