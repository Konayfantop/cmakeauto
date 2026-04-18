#ifndef _CMAKEAUTO_COLORLOGGING_H
#define _CMAKEAUTO_COLORLOGGING_H

#include "commonDecl.h"

#include <stdio.h>
#include <string.h>

#define MAKE_ERROR(arg) \
    do { \
        char expr[128]; \
        expr[0] = '\0'; \
        snprintf(expr, sizeof(expr), "%s%s%s%s%s%s%s", ESC, START, RED, AUTOMAKE, ERROR, arg, RESET); \
        printf("%s\n", expr); \
    }while(0);

#define MAKE_WARNING(arg) \
    do { \
        char expr[128]; \
        expr[0] = '\0'; \
        snprintf(expr, sizeof(expr), "%s%s%s%s%s%s%s", ESC, START, YELLOW, AUTOMAKE, WARNING, arg, RESET); \
        printf("%s\n", expr); \
    }while(0);

#define MAKE_INFO(arg) \
    do { \
        char expr[128]; \
        expr[0] = '\0'; \
        snprintf(expr, sizeof(expr), "%s%s%s%s%s%s%s", ESC, START, GRAY, AUTOMAKE, INFO, arg, RESET); \
        printf("%s\n", expr); \
    }while(0);

#define MAKE_DEBUG(arg) \
    do { \
        char expr[128]; \
        expr[0] = '\0'; \
        snprintf(expr, sizeof(expr), "%s%s%s%s%s%s%s", ESC, START, GRAY, AUTOMAKE, DEBUG, arg, RESET); \
        printf("%s\n", expr); \
    }while(0);

#endif