#ifndef _CMAKEAUTO_COMMONDECL_H
#define _CMAKEAUTO_COMMONDECL_H

#include <stdbool.h>

// For logging MACROS
#define ESC "\x1b" // could be \033
#define AUTOMAKE "[AUTOMAKE"
#define START "["
#define RED "31m"
#define GREEN "32m" 
#define YELLOW "33m"
#define GRAY "90m"
#define RESET "\x1b[0m"
#define ERROR " ERROR] "
#define WARNING " WARNING] "
#define INFO " INFO] "
#define DEBUG " DEBUG] "

enum Aspect
{
    ASPECT_HELP = 1 << 0,
    ASPECT_BUILD = 1 << 1,
    ASPECT_CLEAN = 1 << 2,
    ASPECT_VERSION = 1 << 3
};

#endif