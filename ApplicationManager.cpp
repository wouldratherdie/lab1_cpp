#include "ApplicationManager.h"

#include <iostream>
#include <sstream>
#include <cctype>

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

    std::cout << "\nParameters accepted:\n";
    std::cout << "Speed: " << settings.speed << '\n';
    std::cout << "Line length: " << settings.lineLength << '\n';
    std::cout << "Epilepsy mode: "
        << (settings.epilepsyMode ? "ON" : "OFF") << '\n';

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