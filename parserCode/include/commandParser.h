#ifndef _CMAKEAUTO_COMMANDPARSER_H
#define _CMAKEAUTO_COMMANDPARSER_H

#include <stdbool.h>

typedef enum
{
    ASPECT_HELP = 1 << 0,
    ASPECT_BUILD = 1 << 1,
    ASPECT_CLEAN = 1 << 2,
    ASPECT_VERSION = 1 << 3
} Aspect_t;

unsigned int parseCommandsAndSetFlag(int argumentNum, const char** argValues);
unsigned int parseSingleCommand(const char* singleArg);
unsigned int parseMultipleCommands(const char** argValues);

#endif