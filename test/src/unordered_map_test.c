#include "unity.h"

#include <unordered_map.h>

void test_unorderedMap_initiateProperlyMap(void)
{
    unordered_mapT* aMap = initUnorderedMap();

    TEST_ASSERT_TRUE(aMap != NULL);
    TEST_ASSERT_EQUAL(20u, aMap->size);
    TEST_ASSERT_EQUAL(0u, aMap->capacity);

    for(unsigned int i=0; i<20; ++i)
    {
        TEST_ASSERT_TRUE(aMap->buckets[i] == NULL);
    }
}