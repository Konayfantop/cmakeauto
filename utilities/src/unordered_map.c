#include "unordered_map.h"

#include <string.h>
#include <stdio.h>
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

bucketT* initializeNewNode(const char* const newKey, const char* const newValue)
{
    if(strcmp(newKey, "") == 0 || strcmp(newValue, "") == 0)
    {
        return NULL;
    }

    bucketT* resultNode = (bucketT *)malloc(sizeof(bucketT));

    resultNode->key = (char *)malloc( (strlen(newKey) + 1) * sizeof(char));
    if(resultNode->key == NULL)
    {
        free(resultNode);

        return NULL;
    }

    resultNode->value = (char *)malloc( (strlen(newValue) + 1) * sizeof(char));
    if(resultNode->value == NULL)
    {
        free(resultNode->key);
        free(resultNode);

        return NULL;
    }

    strcpy(resultNode->key, newKey);
    strcpy(resultNode->value, newValue);
    resultNode->next = NULL;

    return resultNode;
}

// REFACTOR IT PLZ
unordered_mapT* initUnorderedMapByCapacity(const unsigned int capacity)
{
    unordered_mapT* unordered_map = (unordered_mapT *)malloc(sizeof(unordered_mapT));
    if(unordered_map == NULL)
    {
        return NULL;
    }

    int i=0;
    unordered_map->buckets = (bucketT **)malloc(sizeof(bucketT *) * capacity);
    for(; i<capacity; ++i)
    {
        unordered_map->buckets[i] = NULL;
    }

    unordered_map->size = 0;
    unordered_map->capacity = capacity;

    return unordered_map;
}

unordered_mapT* initUnorderedMap()
{
    unordered_mapT* unordered_map = (unordered_mapT *)malloc(sizeof(unordered_mapT));
    if(unordered_map == NULL)
    {
        return NULL;
    }

    int i=0;
    unordered_map->buckets = (bucketT **)malloc(sizeof(bucketT *) * DEFAULT_SIZE);
    for(; i<DEFAULT_SIZE; ++i)
    {
        unordered_map->buckets[i] = NULL;
    }

    unordered_map->size = 0;
    unordered_map->capacity = DEFAULT_SIZE;

    return unordered_map;
}

bucketT* find(unordered_mapT* unordered_map, const char* const key)
{
    unsigned long index = hash(key) % unordered_map->capacity;

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

unordered_mapT* triggerRehashing(unordered_mapT* unordered_map, const int oldCapacity, const int newCapacity)
{
    unordered_mapT* newUnorderedMap = initUnorderedMapByCapacity(newCapacity);
    if(newUnorderedMap == NULL)
    {
        return NULL;
    }

    for(int i=0; i<oldCapacity; ++i)
    {
        bucketT* head = unordered_map->buckets[i];
        if(head == NULL)
        {
            continue;
        }

        while(head != NULL)
        {
            unsigned long newIndex = hash(head->key) % newCapacity;

            bucketT* newHead = newUnorderedMap->buckets[newIndex];
            bucketT* nextOfHead = head->next;
            
            head->next = newHead;
            newUnorderedMap->buckets[newIndex] = head;

            head = nextOfHead;
        }
    }

    newUnorderedMap->capacity = newCapacity;
    newUnorderedMap->size = unordered_map->size;
    unordered_map = newUnorderedMap;

    return unordered_map;
}

bucketT* insert(unordered_mapT** unordered_map, const char* const newKey, const char* const newValue)
{
    if( ((double)(*unordered_map)->size / (double)(*unordered_map)->capacity) * 100.0 >= (double)STD_LIMIT_FOR_RESIZING)
    {
        const int oldCapacity = (*unordered_map)->capacity;
        const int newCapacity = 2 * (*unordered_map)->capacity;

        *unordered_map = triggerRehashing(*unordered_map, oldCapacity, newCapacity);
    }

    unsigned long newIndex = hash(newKey) % (*unordered_map)->capacity;

    bucketT* head = (*unordered_map)->buckets[newIndex];
    if(head == NULL)
    {
        bucketT* newNode = initializeNewNode(newKey, newValue);
        if(newNode == NULL)
        {
            return NULL;
        }
        (*unordered_map)->buckets[newIndex] = newNode;
        ++(*unordered_map)->size;
        return head;
    }

    bucketT* curr = head;
    bucketT* prev = NULL;
    while(curr != NULL)
    {
        if(strcmp(curr->key, newKey) == 0)
        {
            char* tmp = (char *)malloc((strlen(newValue) + 1) * sizeof(char));
            if(tmp == NULL)
            {
                return NULL;
            }

            free(curr->value);
            curr->value = tmp;
            strcpy(curr->value, newValue);
            return curr;
        }

        prev = curr;
        curr = curr->next;
    }

    curr = prev; // one node before the end
    bucketT* newNode = initializeNewNode(newKey, newValue);
    if(newNode == NULL)
    {
        return NULL;
    }

    curr->next = newNode;
    newNode->next = NULL;
    ++(*unordered_map)->size;

    return newNode;
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
            --unordered_map->size;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void freeUnorderedMap(unordered_mapT* unordered_map)
{
    if(unordered_map == NULL)
    {
        return;
    }

    for(int i=0; i<unordered_map->capacity; ++i)
    {
        bucketT* curr = unordered_map->buckets[i];
        while(curr != NULL)
        {
            bucketT* tmp = curr;
            curr = curr->next;

            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }
    }

    free(unordered_map->buckets);
    free(unordered_map);
}

void debugMap(unordered_mapT* unordered_map)
{
    if(unordered_map == NULL)
    {
        return;
    }

    for(int i=0; i<unordered_map->capacity; ++i)
    {
        printf("Index : %d -> ", i);

        bucketT* curr = unordered_map->buckets[i];
        while(curr != NULL)
        {
            printf(" %s : %s ", curr->key, curr->value);
            curr = curr->next;
        }
        printf("\n");
    }
}