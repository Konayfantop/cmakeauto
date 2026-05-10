#ifndef _CMAKEAUTO_TOMLDECODING_H
#define _CMAKEAUTO_TOMLDECODING_H

#include <unordered_map.h>

unsigned int parseTomlIfExists();
char* getConfigFilePath();
char* getDirPathContent();
void extractFields(unordered_mapT** unorderedMap, const char* const configDirPath);

#endif