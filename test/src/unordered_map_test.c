#include "unity.h"

#include <string.h>
#include <unordered_map.h>
#include <stdlib.h>
#include <stdbool.h>

bool isKeyValueInMap(unordered_mapT* unordered_map, const char* const newKey, const char* const newValue)
{
    unsigned long index = hash(newKey) % unordered_map->capacity;
    bucketT* curr = unordered_map->buckets[index];

    while(curr != NULL)
    {
        if(strcmp(curr->key, newKey) == 0 && strcmp(curr->value, newValue) == 0)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void test_unorderedMap_simpleHashCheck()
{
    const char* sample = "thereisnospoon";

    // if let's say we have capacity 20
    const unsigned long indexWithCapacity20 = hash(sample) % 20;
    TEST_ASSERT_EQUAL(indexWithCapacity20, 13);

    const unsigned long indexWithCapacity80 = hash(sample) % 80;
    TEST_ASSERT_EQUAL(indexWithCapacity80, 53);
}

void test_unorderedMap_initializeNewNode(void)
{
    bucketT* newBucket = initializeNewNode("key", "value");

    TEST_ASSERT_TRUE(newBucket != NULL);
    TEST_ASSERT_EQUAL(0, strcmp("key", newBucket->key));
    TEST_ASSERT_EQUAL(0, strcmp("value", newBucket->value));
    TEST_ASSERT_EQUAL(NULL, newBucket->next);

    free(newBucket);
}

void test_unorderedMap_initiateProperlyMap(void)
{
    unordered_mapT* aMap = initUnorderedMap();

    TEST_ASSERT_TRUE(aMap != NULL);
    TEST_ASSERT_EQUAL(0u, aMap->size);
    TEST_ASSERT_EQUAL(20u, aMap->capacity);

    for(unsigned int i=0; i<20; ++i)
    {
        TEST_ASSERT_TRUE(aMap->buckets[i] == NULL);
    }

    freeUnorderedMap(aMap);
}

void test_unorderedMap_insertPair(void)
{
    unordered_mapT* aMap = initUnorderedMap();
    TEST_ASSERT_TRUE(aMap != NULL);

    insert(&aMap, "key", "value");

    // custom made find and not the actual find as we test one thing at a time
    TEST_ASSERT_TRUE(isKeyValueInMap(aMap, "key", "value"));

    freeUnorderedMap(aMap);
}

void test_unorderedMap_insertAlreadyKeyToOverwriteValue(void)
{
    unordered_mapT* aMap = initUnorderedMap();
    TEST_ASSERT_TRUE(aMap != NULL);

    insert(&aMap, "key", "value");
    insert(&aMap, "key", "overwriteValue");

    // custom made find and not the actual find as we test one thing at a time
    TEST_ASSERT_TRUE(isKeyValueInMap(aMap, "key", "overwriteValue"));

    freeUnorderedMap(aMap);
}

void test_unorderedMap_insertPairsToTriggerResize(void)
{
    unordered_mapT* aMap = initUnorderedMap();
    TEST_ASSERT_TRUE(aMap != NULL);

    insert(&aMap, "a", "aa");
    insert(&aMap, "b", "bb");
    insert(&aMap, "c", "cc");
    insert(&aMap, "d", "dd");
    insert(&aMap, "e", "ee");
    insert(&aMap, "f", "ff");
    insert(&aMap, "g", "gg");
    insert(&aMap, "h", "hh");
    insert(&aMap, "i", "ii");
    insert(&aMap, "j", "jj");
    insert(&aMap, "k", "kk");
    insert(&aMap, "l", "ll");
    insert(&aMap, "m", "mm");
    insert(&aMap, "abc", "aabbcc"); // this one must be moved due to rehashing


    // at that point we don't trigger reallocation
    unsigned long indexForA = hash("a") % aMap->capacity;
    unsigned long indexForH = hash("h") % aMap->capacity;
    unsigned long indexForM = hash("m") % aMap->capacity;
    unsigned long indexForAbc = hash("abc") % aMap->capacity;

    TEST_ASSERT_EQUAL(10ul, indexForA);
    TEST_ASSERT_EQUAL(17ul, indexForH);
    TEST_ASSERT_EQUAL(2ul, indexForM);
    TEST_ASSERT_EQUAL(3ul, indexForAbc);

    TEST_ASSERT_NOT_EQUAL(40, aMap->capacity);
    TEST_ASSERT_EQUAL(20, aMap->capacity);

    // trigger reallocation
    insert(&aMap, "o", "oo");
    insert(&aMap, "p", "pp");

    TEST_ASSERT_NOT_EQUAL(20, aMap->capacity);
    TEST_ASSERT_EQUAL(40, aMap->capacity);

    // reallocation is a number way bigger than before so we must check rehashing problems
    unsigned long newIndexForA = hash("a") % aMap->capacity;
    unsigned long newIndexForH = hash("h") % aMap->capacity;
    unsigned long newIndexForM = hash("m") % aMap->capacity;
    unsigned long newIndexForAbc = hash("abc") % aMap->capacity;


    TEST_ASSERT_EQUAL(30ul, newIndexForA);
    TEST_ASSERT_EQUAL(37ul, newIndexForH);
    TEST_ASSERT_EQUAL(2ul, newIndexForM);
    TEST_ASSERT_EQUAL(3ul, newIndexForAbc);

    freeUnorderedMap(aMap);
}

void test_unorderedMap_insertPairsToTriggerMoreCollisionsOnRehashing(void)
{
    unordered_mapT* aMap = initUnorderedMap();
    TEST_ASSERT_TRUE(aMap != NULL);

    insert(&aMap, "abc", "aabbcc");
    insert(&aMap, "acb", "aaccbb");
    insert(&aMap, "bac", "bbaacc");
    insert(&aMap, "bca", "bbccaa");
    insert(&aMap, "bcae", "bbccaaee");
    insert(&aMap, "f", "ff");
    insert(&aMap, "g", "gg");
    insert(&aMap, "h", "hh");
    insert(&aMap, "i", "ii");
    insert(&aMap, "j", "jj");
    insert(&aMap, "k", "kk");
    insert(&aMap, "l", "ll");
    insert(&aMap, "m", "mm");
    insert(&aMap, "n", "nn");

    unsigned long indexForAbc = hash("abc") % aMap->capacity;
    unsigned long indexForAcb = hash("acb") % aMap->capacity;
    unsigned long indexForBac = hash("bac") % aMap->capacity;
    unsigned long indexForBca = hash("bca") % aMap->capacity;
    unsigned long indexForBcae = hash("bcae") % aMap->capacity;
    unsigned long indexForF = hash("f") % aMap->capacity;
    unsigned long indexForG = hash("g") % aMap->capacity;
    unsigned long indexForH = hash("h") % aMap->capacity;
    unsigned long indexForI = hash("i") % aMap->capacity;
    unsigned long indexForJ = hash("j") % aMap->capacity;
    unsigned long indexForK = hash("k") % aMap->capacity;
    unsigned long indexForL = hash("l") % aMap->capacity;
    unsigned long indexForM = hash("m") % aMap->capacity;
    unsigned long indexForN = hash("n") % aMap->capacity;

    TEST_ASSERT_EQUAL(3ul, indexForAbc);
    TEST_ASSERT_EQUAL(15ul, indexForAcb);
    TEST_ASSERT_EQUAL(19ul, indexForBac);
    TEST_ASSERT_EQUAL(3ul, indexForBca);
    TEST_ASSERT_EQUAL(0ul, indexForBcae);
    TEST_ASSERT_EQUAL(15ul, indexForF);
    TEST_ASSERT_EQUAL(16ul, indexForG);
    TEST_ASSERT_EQUAL(17ul, indexForH);
    TEST_ASSERT_EQUAL(18ul, indexForI);
    TEST_ASSERT_EQUAL(19ul, indexForJ);
    TEST_ASSERT_EQUAL(0ul, indexForK);
    TEST_ASSERT_EQUAL(1ul, indexForL);
    TEST_ASSERT_EQUAL(2ul, indexForM);
    TEST_ASSERT_EQUAL(3ul, indexForN);

    // trigger reallocation
    insert(&aMap, "w", "ww");
    insert(&aMap, "x", "xx");
    insert(&aMap, "z", "zz");

    TEST_ASSERT_NOT_EQUAL(20, aMap->capacity);
    TEST_ASSERT_EQUAL(40, aMap->capacity);

    unsigned long newIndexForAbc = hash("abc") % aMap->capacity;
    unsigned long newIndexForAcb = hash("acb") % aMap->capacity;
    unsigned long newIndexForBac = hash("bac") % aMap->capacity;
    unsigned long newIndexForBca = hash("bca") % aMap->capacity;
    unsigned long newIndexForBcae = hash("bcae") % aMap->capacity;
    unsigned long newIndexForF = hash("f") % aMap->capacity;
    unsigned long newIndexForG = hash("g") % aMap->capacity;
    unsigned long newIndexForH = hash("h") % aMap->capacity;
    unsigned long newIndexForI = hash("i") % aMap->capacity;
    unsigned long newIndexForJ = hash("j") % aMap->capacity;
    unsigned long newIndexForK = hash("k") % aMap->capacity;
    unsigned long newIndexForL = hash("l") % aMap->capacity;
    unsigned long newIndexForM = hash("m") % aMap->capacity;
    unsigned long newIndexForN = hash("n") % aMap->capacity;

    TEST_ASSERT_EQUAL(3ul, newIndexForAbc);
    TEST_ASSERT_EQUAL(35ul, newIndexForAcb);
    TEST_ASSERT_EQUAL(19ul, newIndexForBac);
    TEST_ASSERT_EQUAL(3ul, newIndexForBca);
    TEST_ASSERT_EQUAL(0ul, newIndexForBcae);
    TEST_ASSERT_EQUAL(35ul, newIndexForF);
    TEST_ASSERT_EQUAL(36ul, newIndexForG);
    TEST_ASSERT_EQUAL(37ul, newIndexForH);
    TEST_ASSERT_EQUAL(38ul, newIndexForI);
    TEST_ASSERT_EQUAL(39ul, newIndexForJ);
    TEST_ASSERT_EQUAL(0ul, newIndexForK);
    TEST_ASSERT_EQUAL(1ul, newIndexForL);
    TEST_ASSERT_EQUAL(2ul, newIndexForM);
    TEST_ASSERT_EQUAL(3ul, newIndexForN);

    freeUnorderedMap(aMap);
}

void test_unorderedMap_insertPairsToTriggerMoreCollisionsOnRehashingCheckStructure(void)
{
    unordered_mapT* aMap = initUnorderedMap();
    TEST_ASSERT_TRUE(aMap != NULL);

    insert(&aMap, "abc", "aabbcc");
    insert(&aMap, "acb", "aaccbb");
    insert(&aMap, "bac", "bbaacc");
    insert(&aMap, "bca", "bbccaa");
    insert(&aMap, "bcae", "bbccaaee");
    insert(&aMap, "f", "ff");
    insert(&aMap, "g", "gg");
    insert(&aMap, "h", "hh");
    insert(&aMap, "i", "ii");
    insert(&aMap, "j", "jj");
    insert(&aMap, "k", "kk");
    insert(&aMap, "l", "ll");
    insert(&aMap, "m", "mm");
    insert(&aMap, "n", "nn");
    insert(&aMap, "w", "ww");
    insert(&aMap, "x", "xx");
    insert(&aMap, "z", "zz");

    TEST_ASSERT_NOT_EQUAL(20, aMap->capacity);
    TEST_ASSERT_EQUAL(40, aMap->capacity);

    // visualization 
    // Index : 0 ->  k  bcae 
    // Index : 1 ->  l 
    // Index : 2 ->  m 
    // Index : 3 ->  n  bca  abc 
    // Index : 4 -> 
    // Index : 5 -> 
    // Index : 6 -> 
    // Index : 7 -> 
    // Index : 8 -> 
    // Index : 9 -> 
    // Index : 10 -> 
    // Index : 11 -> 
    // Index : 12 ->  w 
    // Index : 13 ->  x 
    // Index : 14 -> 
    // Index : 15 ->  z 
    // Index : 16 -> 
    // Index : 17 -> 
    // Index : 18 -> 
    // Index : 19 ->  bac 
    // Index : 20 -> 
    // Index : 21 -> 
    // Index : 22 -> 
    // Index : 23 -> 
    // Index : 24 -> 
    // Index : 25 -> 
    // Index : 26 -> 
    // Index : 27 -> 
    // Index : 28 -> 
    // Index : 29 -> 
    // Index : 30 -> 
    // Index : 31 -> 
    // Index : 32 -> 
    // Index : 33 -> 
    // Index : 34 -> 
    // Index : 35 ->  f  acb 
    // Index : 36 ->  g 
    // Index : 37 ->  h 
    // Index : 38 ->  i 
    // Index : 39 ->  j


    bucketT* head0 = aMap->buckets[0];
    bucketT* head3 = aMap->buckets[3];
    bucketT* head35 = aMap->buckets[35];

    // index 0
    bucketT* curr = head0;
    TEST_ASSERT_EQUAL(0, strcmp(curr->key, "k"));
    curr = curr->next;
    TEST_ASSERT_EQUAL(0, strcmp(curr->key, "bcae"));
    curr = curr->next;
    TEST_ASSERT_EQUAL(NULL, curr);

    // index 1
    TEST_ASSERT_EQUAL(0, strcmp(aMap->buckets[1]->key, "l"));
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[1]->next);

    // index 2
    TEST_ASSERT_EQUAL(0, strcmp(aMap->buckets[2]->key, "m"));
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[2]->next);

    // index 3
    curr = head3;
    TEST_ASSERT_EQUAL(0, strcmp(curr->key, "n"));
    curr = curr->next;
    TEST_ASSERT_EQUAL(0, strcmp(curr->key, "bca"));
    curr = curr->next;
    TEST_ASSERT_EQUAL(0, strcmp(curr->key, "abc"));
    curr = curr->next;
    TEST_ASSERT_EQUAL(NULL, curr);

    // index 12
    TEST_ASSERT_EQUAL(0, strcmp(aMap->buckets[12]->key, "w"));
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[12]->next);
    
    // index 13
    TEST_ASSERT_EQUAL(0, strcmp(aMap->buckets[13]->key, "x"));
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[13]->next);

    // index 15
    TEST_ASSERT_EQUAL(0, strcmp(aMap->buckets[15]->key, "z"));
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[15]->next);

    // index 19
    TEST_ASSERT_EQUAL(0, strcmp(aMap->buckets[19]->key, "bac"));
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[19]->next);

    // index 35
    curr = head35;
    TEST_ASSERT_EQUAL(0, strcmp(curr->key, "f"));
    curr = curr->next;
    TEST_ASSERT_EQUAL(0, strcmp(curr->key, "acb"));
    curr = curr->next;
    TEST_ASSERT_EQUAL(NULL, curr);

    // index 36
    TEST_ASSERT_EQUAL(0, strcmp(aMap->buckets[36]->key, "g"));
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[36]->next);

    // index 37
    TEST_ASSERT_EQUAL(0, strcmp(aMap->buckets[37]->key, "h"));
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[37]->next);

    // index 38
    TEST_ASSERT_EQUAL(0, strcmp(aMap->buckets[38]->key, "i"));
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[38]->next);

    // index 39
    TEST_ASSERT_EQUAL(0, strcmp(aMap->buckets[39]->key, "j"));
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[39]->next);

    // null indexes
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[4]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[5]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[6]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[7]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[8]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[9]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[10]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[11]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[14]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[16]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[17]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[18]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[20]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[21]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[22]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[23]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[24]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[25]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[26]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[27]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[28]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[29]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[30]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[31]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[32]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[33]);
    TEST_ASSERT_EQUAL(NULL, aMap->buckets[34]);

    freeUnorderedMap(aMap);
}

void test_unordered_map_testFindNodesExistingOrNot(void)
{
    unordered_mapT* aMap = initUnorderedMap();
    TEST_ASSERT_TRUE(aMap != NULL);

    insert(&aMap, "abc", "aabbcc");
    insert(&aMap, "acb", "aaccbb");
    insert(&aMap, "bac", "bbaacc");
    insert(&aMap, "bca", "bbccaa");
    insert(&aMap, "bcae", "bbccaaee");
    insert(&aMap, "f", "ff");
    insert(&aMap, "g", "gg");
    insert(&aMap, "h", "hh");
    insert(&aMap, "i", "ii");

    bucketT* nodeFound = find(aMap, "bcae");
    bucketT* nodeNotFound = find(aMap, "WHAT?");

    TEST_ASSERT_TRUE(nodeFound != NULL);
    TEST_ASSERT_EQUAL(0, strcmp(nodeFound->key, "bcae"));
    TEST_ASSERT_EQUAL(0, strcmp(nodeFound->value, "bbccaaee"));

    TEST_ASSERT_TRUE(nodeNotFound == NULL);

    freeUnorderedMap(aMap);
}

void test_unordered_map_testEraseNodesExistingOrNot(void)
{
    unordered_mapT* aMap = initUnorderedMap();
    TEST_ASSERT_TRUE(aMap != NULL);

    insert(&aMap, "abc", "aabbcc");
    insert(&aMap, "acb", "aaccbb");
    insert(&aMap, "bac", "bbaacc");
    insert(&aMap, "bca", "bbccaa");
    insert(&aMap, "bcae", "bbccaaee");
    insert(&aMap, "f", "ff");
    insert(&aMap, "g", "gg");
    insert(&aMap, "h", "hh");
    insert(&aMap, "i", "ii");

    TEST_ASSERT_EQUAL(9u, aMap->size);
    TEST_ASSERT_TRUE(erase(aMap, "abc"));
    TEST_ASSERT_EQUAL(8u, aMap->size);

    TEST_ASSERT_EQUAL(NULL, find(aMap, "abc"));

    TEST_ASSERT_FALSE(erase(aMap, "WHAT?"));
    TEST_ASSERT_EQUAL(8u, aMap->size);
}