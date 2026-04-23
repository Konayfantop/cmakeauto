#ifndef _CMAKEAUTO_COMMANDPARSER_H
#define _CMAKEAUTO_COMMANDPARSER_H

#include <stdbool.h>

unsigned int parseCommandsAndSetFlag(int argumentNum, const char** argValues);
unsigned int parseSingleCommand(const char* singleArg);
unsigned int parseMultipleCommands(const char** argValues);

#endif