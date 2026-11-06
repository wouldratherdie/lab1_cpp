#pragma once

#include <string>

class ApplicationManager
{
public:
    int run(int argumentCount, char* arguments[]);

private:
    struct Settings
    {
        int speed;
        int lineLength;
        bool epilepsyMode;
    };

    bool readInteractiveSettings(Settings& settings) const;

    bool parseCommandLine(
        int argumentCount,
        char* arguments[],
        Settings& settings
    ) const;

    static bool parseInteger(
        const std::string& text,
        int minimum,
        int maximum,
        int& result
    );

    static void showHelp();

    bool runAnimation(const Settings& settings) const;
};