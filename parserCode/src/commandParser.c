#include "commandParser.h"

#include "colorLogging.h"

#include <string.h>

unsigned int parseCommandsAndSetFlag(int argumentNum, const char** argValues)
{
    unsigned int flags = 0;

    if(argumentNum == 1)
    {
        MAKE_ERROR("No arguments, type --help if needed");
    }
    else if(argumentNum == 2)
    {
        flags = parseSingleCommand(argValues[1]);
    }
    else
    {
        flags = parseMultipleCommands(argValues);
    }

    return flags;
}

unsigned int parseSingleCommand(const char* singleArg)
{
    unsigned int flags = 0;

    if(strcmp(singleArg, "--help") == 0)
    {
        flags = ASPECT_HELP;
    }
    else if(strcmp(singleArg, "build") == 0)
    {
        flags = ASPECT_BUILD;
    }
    else if(strcmp(singleArg, "clean") == 0)
    {
        flags = ASPECT_CLEAN;
    }
    else if(strcmp(singleArg, "--V") == 0 || strcmp(singleArg, "--version") == 0)
    {
        flags = ASPECT_VERSION;
    }
    else
    {
        MAKE_ERROR("Argument not understood, type --help for choices");
    }
    return flags;
}

unsigned int parseMultipleCommands(const char** argValues)
{
    unsigned int flags = 0;

    return flags;
}