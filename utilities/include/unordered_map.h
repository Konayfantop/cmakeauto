#ifndef _CMAKEAUTO_UNORDERED_MAP_H
#define _CMAKEAUTO_UNORDERED_MAP_H

#include <stdbool.h>

#define DEFAULT_SIZE 20
#define STD_LIMIT_FOR_RESIZING 75 // 75%

// node description of the unordered_map and utilities;
typedef struct bucket
{
    char* key;
    char* value;

    struct bucket* next;
}bucketT;

// we always start with 20 buckets by default. When to resize ?
// resize when the size and the current items are 75%
typedef struct unordered_map
{
    bucketT** buckets;
    unsigned int size;
    unsigned int capacity;

}unordered_mapT;

unsigned long hash(const char *str);
unordered_mapT* initUnorderedMap();
unordered_mapT* initUnorderedMapByCapacity(const unsigned int capacity);
bucketT* initializeNewNode(const char* const newKey, const char* const newValue);
bucketT* insert(unordered_mapT** unordered_map, const char* const newKey, const char* const newValue);
bucketT* find(unordered_mapT* const unordered_map, const char* const key);
bool erase(unordered_mapT* unordered_map, const char* const key);
void freeUnorderedMap(unordered_mapT* unordered_map);
void debugMap(unordered_mapT* unordered_map);

#endif