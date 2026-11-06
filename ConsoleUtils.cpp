#include "ConsoleUtils.h"

#include <Windows.h>
#include <climits>

namespace
{
    // Converts a symbol color to a WinAPI console color.
    WORD getConsoleColor(SymbolColor color)
    {
        switch (color)
        {
        case SymbolColor::Green:
            return FOREGROUND_GREEN | FOREGROUND_INTENSITY;

        case SymbolColor::Blue:
            return FOREGROUND_BLUE | FOREGROUND_INTENSITY;

        case SymbolColor::Cyan:
            return FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

        case SymbolColor::Red:
            return FOREGROUND_RED | FOREGROUND_INTENSITY;

        case SymbolColor::Magenta:
            return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

        case SymbolColor::Yellow:
            return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

        case SymbolColor::White:
        default:
            return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        }
    }
}

bool ConsoleUtils::setCursorPosition(int x, int y)
{
    if (x < 0 || y < 0 || x > SHRT_MAX || y > SHRT_MAX)
        return false;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    if (console == INVALID_HANDLE_VALUE)
        return false;

    COORD position =
    {
        static_cast<SHORT>(x),
        static_cast<SHORT>(y)
    };

    return SetConsoleCursorPosition(console, position) != 0;
}

bool ConsoleUtils::setTextColor(SymbolColor color)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    if (console == INVALID_HANDLE_VALUE)
        return false;

    return SetConsoleTextAttribute(console, getConsoleColor(color)) != 0;
}

bool ConsoleUtils::clearScreen()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;

    if (console == INVALID_HANDLE_VALUE ||
        !GetConsoleScreenBufferInfo(console, &info))
        return false;

    DWORD cellCount = info.dwSize.X * info.dwSize.Y;
    DWORD written = 0;
    COORD home = { 0, 0 };

    if (!FillConsoleOutputCharacterA(console, ' ', cellCount, home, &written))
        return false;

    if (!FillConsoleOutputAttribute(
        console, info.wAttributes, cellCount, home, &written))
        return false;

    return SetConsoleCursorPosition(console, home) != 0;
}

bool ConsoleUtils::setCursorVisible(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    if (console == INVALID_HANDLE_VALUE ||
        !GetConsoleCursorInfo(console, &cursorInfo))
        return false;

    cursorInfo.bVisible = visible;

    return SetConsoleCursorInfo(console, &cursorInfo) != 0;
}

bool ConsoleUtils::getWindowSize(int& width, int& height)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;

    if (console == INVALID_HANDLE_VALUE ||
        !GetConsoleScreenBufferInfo(console, &info))
        return false;

    width = info.srWindow.Right - info.srWindow.Left + 1;
    height = info.srWindow.Bottom - info.srWindow.Top + 1;

    return true;
}

bool ConsoleUtils::drawSymbol(int x, int y, const Symbol& symbol)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    if (console == nullptr || console == INVALID_HANDLE_VALUE)
        return false;

    if (!setCursorPosition(x, y) || !setTextColor(symbol.getColor()))
        return false;

    char value = symbol.getValue();
    DWORD written = 0;

    return WriteConsoleA(console, &value, 1, &written, nullptr)
        && written == 1;
}

bool ConsoleUtils::eraseCharacter(int x, int y)
{
    if (!setCursorPosition(x, y))
        return false;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written = 0;
    const char blank = ' ';

    return WriteConsoleA(console, &blank, 1, &written, nullptr)
        && written == 1;
}