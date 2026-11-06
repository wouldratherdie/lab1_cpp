#pragma once

#include <string>

// Controls the application workflow.
class ApplicationManager
{
public:
    // Starts the application.
    int run(int argumentCount, char* arguments[]);

private:
    // Stores application settings.
    struct Settings
    {
        int speed;
        int lineLength;
        bool epilepsyMode;
    };

    // Reads settings interactively.
    bool readInteractiveSettings(Settings& settings) const;

    // Parses command line arguments.
    bool parseCommandLine(
        int argumentCount,
        char* arguments[],
        Settings& settings
    ) const;

    // Validates and converts an integer.
    static bool parseInteger(
        const std::string& text,
        int minimum,
        int maximum,
        int& result
    );

    // Displays command line help.
    static void showHelp();

    // Runs the Matrix animation.
    bool runAnimation(const Settings& settings) const;
};