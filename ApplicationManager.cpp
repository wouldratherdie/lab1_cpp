#include "ApplicationManager.h"
#include "Line.h"
#include "ConsoleUtils.h"

#include <array>
#include <chrono>
#include <conio.h>
#include <memory>
#include <random>
#include <thread>
#include <iostream>
#include <sstream>
#include <cctype>

namespace
{
    // Selects a color for the entire line.
    SymbolColor selectLineColor(
        bool epilepsyMode,
        std::mt19937& generator)
    {
        if (!epilepsyMode)
            return SymbolColor::Green;

        static const std::array<SymbolColor, 7> colors =
        {
            SymbolColor::Green,
            SymbolColor::Blue,
            SymbolColor::Cyan,
            SymbolColor::Red,
            SymbolColor::Magenta,
            SymbolColor::Yellow,
            SymbolColor::White
        };

        std::uniform_int_distribution<int> distribution(
            0, static_cast<int>(colors.size()) - 1
        );

        return colors[distribution(generator)];
    }
}

int ApplicationManager::run(int argumentCount, char* arguments[])
{
    Settings settings{};

    if (argumentCount == 1)
    {
        if (!readInteractiveSettings(settings))
            return 1;
    }
    else if (argumentCount == 2 &&
        (std::string(arguments[1]) == "--help" ||
            std::string(arguments[1]) == "/?"))
    {
        showHelp();
        return 0;
    }
    else
    {
        if (!parseCommandLine(argumentCount, arguments, settings))
        {
            std::cerr << "Invalid command line arguments.\n";
            showHelp();
            return 1;
        }
    }

    if (!runAnimation(settings))
    {
        std::cerr << "Unable to initialize console animation.\n";
        return 1;
    }

    return 0;
}

bool ApplicationManager::parseInteger(
    const std::string& text,
    int minimum,
    int maximum,
    int& result)
{
    std::istringstream stream(text);
    char extraCharacter;

    if (!(stream >> result) || (stream >> extraCharacter))
        return false;

    return result >= minimum && result <= maximum;
}

bool ApplicationManager::readInteractiveSettings(Settings& settings) const
{
    std::string input;

    while (true)
    {
        std::cout << "Enter speed (1-30): ";

        if (!std::getline(std::cin, input))
            return false;

        if (parseInteger(input, 1, 30, settings.speed))
            break;

        std::cout << "Invalid speed. Try again.\n";
    }

    while (true)
    {
        std::cout << "Enter line length (1-30): ";

        if (!std::getline(std::cin, input))
            return false;

        if (parseInteger(input, 1, 30, settings.lineLength))
            break;

        std::cout << "Invalid length. Try again.\n";
    }

    while (true)
    {
        std::cout << "Enable epilepsy mode (Y/N): ";

        if (!std::getline(std::cin, input))
            return false;

        if (input.size() == 1)
        {
            char answer = static_cast<char>(
                std::toupper(static_cast<unsigned char>(input[0]))
                );

            if (answer == 'Y' || answer == 'N')
            {
                settings.epilepsyMode = (answer == 'Y');
                break;
            }
        }

        std::cout << "Enter Y or N.\n";
    }

    return true;
}

bool ApplicationManager::parseCommandLine(
    int argumentCount,
    char* arguments[],
    Settings& settings) const
{
    if (argumentCount != 4)
        return false;

    if (!parseInteger(arguments[1], 1, 30, settings.speed))
        return false;

    if (!parseInteger(arguments[2], 1, 30, settings.lineLength))
        return false;

    std::string answer = arguments[3];

    if (answer.size() != 1)
        return false;

    char mode = static_cast<char>(
        std::toupper(static_cast<unsigned char>(answer[0]))
        );

    if (mode != 'Y' && mode != 'N')
        return false;

    settings.epilepsyMode = (mode == 'Y');

    return true;
}

void ApplicationManager::showHelp()
{
    std::cout
        << "Matrix - Command Line Help\n\n"
        << "Usage:\n"
        << "  lab1_cpp.exe <speed> <length> <Y/N>\n\n"
        << "Parameters:\n"
        << "  speed  - Line speed (1-30)\n"
        << "  length - Line length (1-30)\n"
        << "  Y/N    - Enable or disable epilepsy mode\n\n"
        << "Examples:\n"
        << "  lab1_cpp.exe 23 8 Y\n"
        << "  lab1_cpp.exe 10 15 N\n\n"
        << "Help:\n"
        << "  lab1_cpp.exe --help\n"
        << "  lab1_cpp.exe /?\n";
}

bool ApplicationManager::runAnimation(const Settings& settings) const
{
    int windowWidth = 0;
    int windowHeight = 0;

    if (!ConsoleUtils::getWindowSize(windowWidth, windowHeight) ||
        windowWidth <= 0 || windowHeight <= 0)
        return false;

    std::cout << "\nPress any key to stop the animation...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(900));

    if (!ConsoleUtils::clearScreen())
        return false;

    if (!ConsoleUtils::setCursorVisible(false))
        return false;

    std::mt19937 generator(std::random_device{}());

    std::uniform_int_distribution<int> xDistribution(
        0, windowWidth - 1
    );

    std::unique_ptr<Line> line;

    const auto stepDuration =
        std::chrono::duration_cast<std::chrono::steady_clock::duration>(
            std::chrono::duration<double>(1.0 / settings.speed)
        );

    auto nextStep = std::chrono::steady_clock::now();

    while (!_kbhit())
    {
        if (!line || line->isFinished())
        {
            int xPosition = xDistribution(generator);

            SymbolColor color = selectLineColor(
                settings.epilepsyMode, generator
            );

            line = std::make_unique<Line>(
                xPosition,
                settings.lineLength,
                windowHeight,
                color
            );
        }

        line->advance();

        nextStep += stepDuration;
        std::this_thread::sleep_until(nextStep);
    }

    _getch();

    line.reset();

    ConsoleUtils::clearScreen();
    ConsoleUtils::setTextColor(SymbolColor::Green);
    ConsoleUtils::setCursorVisible(true);

    std::cout << "Animation stopped.\n";

    return true;
}