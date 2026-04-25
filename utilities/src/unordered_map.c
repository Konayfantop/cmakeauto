#include "unordered_map.h"

#include <string.h>
#include <stdlib.h>

unsigned long hash(const char *str)
{
    unsigned long h = 5381;
    int c;

    while ((c = *str++))
    {
        h = ((h << 5) + h) + c; // h * 33 + c
    }

    return h;
}

unordered_mapT* initUnorderedMap()
{
    unordered_mapT* unordered_map = (unordered_mapT *)malloc(sizeof(unordered_mapT));
    if(unordered_map == NULL)
    {
        return NULL;
    }

    unordered_map->buckets = (bucketT **)malloc(sizeof(bucketT *) * DEFAULT_SIZE);
    for(int i=0; i<DEFAULT_SIZE; ++i)
    {
        unordered_map->buckets[i] = (bucketT *)malloc(sizeof(bucketT));
        unordered_map->buckets[i] = NULL;
    }

    unordered_map->size = 20;
    unordered_map->capacity = 0;

    return unordered_map;
}

bucketT* initializeNewNode(const char* const newKey, const char* const newValue)
{
    bucketT* resultNode = (bucketT *)malloc(sizeof(bucketT));

    resultNode->key = (char *)malloc( (strlen(newKey) + 1) * sizeof(char));
    if(resultNode->key == NULL)
    {
        return NULL;
    }

    resultNode->value = (char *)malloc( (strlen(newValue) + 1) * sizeof(char));
    if(resultNode->value == NULL)
    {
        return NULL;
    }

    strcpy(resultNode->key, newKey);
    strcpy(resultNode->value, newValue);
    
    resultNode->next = NULL;

    return resultNode;
}

bucketT* insert(unordered_mapT* unordered_map, const char* const newKey, const char* const newValue)
{
    unsigned long newIndex = hash(newKey) % unordered_map->size;
    bucketT* resultNode;
    if(unordered_map->buckets[newIndex] == NULL)
    {
        if( ((double)unordered_map->capacity / (double)unordered_map->size) * 100 >= STD_LIMIT_FOR_RESIZING)
        {
            const int newSize = unordered_map->size * unordered_map->size;
            unordered_mapT* tmp = (unordered_mapT *)realloc(unordered_map, newSize);
            if(tmp != NULL)
            {
                unordered_map = tmp;
                newIndex = hash(newKey) % unordered_map->size;
                unordered_map->capacity = newSize;
            }
        }

        resultNode = initializeNewNode(newKey, newValue);
        
        unordered_map->buckets[newIndex] = resultNode;
        ++unordered_map->size;
    }
    else
    {
        bucketT* prev = NULL;
        bucketT* curr = unordered_map->buckets[newIndex];
        while(curr != NULL)
        {
            if(curr->key == newKey)
            {
                // overwriting the value given the same key
                free(curr->value);

                resultNode->value = (char *)malloc( (strlen(newValue) + 1) * sizeof(char));
                if(resultNode->value == NULL)
                {
                    return NULL;
                }
                strcpy(resultNode->value, newValue);

                resultNode = curr;
                break;
            }
            prev = curr;
            curr = curr->next;
        }

        resultNode = initializeNewNode(newKey, newValue);
        ++unordered_map->size;

        prev->next = resultNode;
    }
    return resultNode;
}

bucketT* find(unordered_mapT* unordered_map, const char* const key)
{
    unsigned long index = hash(key) % unordered_map->size;

    bucketT* curr = unordered_map->buckets[index];
    while(curr != NULL)
    {
        if( strcmp(key, curr->key) == 0 )
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

bool erase(unordered_mapT* unordered_map, const char* const key)
{
    unsigned long index = hash(key) % unordered_map->size;

    bucketT* prev = NULL;
    bucketT* head = unordered_map->buckets[index];
    bucketT* curr = head;

    while(curr != NULL)
    {
        if( strcmp(key, curr->key) == 0 )
        {
            if(curr == head)
            {
                head = head->next;
                unordered_map->buckets[index] = head;
            }
            else
            {
                prev->next = curr->next;
            }

            free(curr);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}