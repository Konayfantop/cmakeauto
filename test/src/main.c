#include "unity.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char* originalPath;

void setUp(void) 
{
    originalPath = (char *)malloc(sizeof(char) * 5000);
    getcwd(originalPath, 1000);
}

void tearDown(void)
{
    chdir(originalPath);
    free(originalPath);
}

// tomlDecoding section
void test_tomlDecoding_findProperlyTheContentsOfThePathWhenFoldersExist(void);
void test_tomlDecoding_findProperlyTheContentsOfThePathWhenFilesExist(void);
void test_tomlDecoding_notAbleTofindTheAutomakeConfigFileDirPath(void);
void test_tomlDecoding_findTheAutomakeConfigFileDirPath(void);
void test_tomlDecoding_decodeSimpleToml(void);
void test_tomlDecoding_decodeTomlFullOfCommentsOnThePairs(void);
void test_tomlDecoding_decodeTomlFullOfCommentsWherever(void);
void test_tomlDecoding_decodeTomlFullOfCommentsWhereverButWithoutEmptyLineInTheEnd(void);
void test_tomlDecoding_decodeTomlFullOfCommentsButWithHeaderInTheEndWithoutValues(void);
void test_tomlDecoding_decodeTomlsimpleInputButKeysWithoutValue(void);

// unordered_map section
void test_unorderedMap_initiateProperlyMap(void);
void test_unorderedMap_simpleHashCheck(void);
void test_unorderedMap_initializeNewNode(void);
void test_unorderedMap_insertPair(void);
void test_unorderedMap_insertAlreadyKeyToOverwriteValue(void);
void test_unorderedMap_insertPairsToTriggerResize(void);
void test_unorderedMap_insertPairsToTriggerMoreCollisionsOnRehashing(void);
void test_unorderedMap_insertPairsToTriggerMoreCollisionsOnRehashingCheckStructure(void);
void test_unordered_map_testFindNodesExistingOrNot(void);
void test_unordered_map_testEraseNodesExistingOrNot(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_tomlDecoding_findProperlyTheContentsOfThePathWhenFoldersExist);
    RUN_TEST(test_tomlDecoding_findProperlyTheContentsOfThePathWhenFilesExist);
    RUN_TEST(test_tomlDecoding_notAbleTofindTheAutomakeConfigFileDirPath);
    RUN_TEST(test_tomlDecoding_findTheAutomakeConfigFileDirPath);
    RUN_TEST(test_tomlDecoding_decodeSimpleToml);
    RUN_TEST(test_tomlDecoding_decodeTomlFullOfCommentsOnThePairs);
    RUN_TEST(test_tomlDecoding_decodeTomlFullOfCommentsWherever);
    RUN_TEST(test_tomlDecoding_decodeTomlFullOfCommentsWhereverButWithoutEmptyLineInTheEnd);
    RUN_TEST(test_tomlDecoding_decodeTomlFullOfCommentsButWithHeaderInTheEndWithoutValues);
    RUN_TEST(test_tomlDecoding_decodeTomlsimpleInputButKeysWithoutValue);

    RUN_TEST(test_unorderedMap_initiateProperlyMap);
    RUN_TEST(test_unorderedMap_initializeNewNode);
    RUN_TEST(test_unorderedMap_simpleHashCheck);
    RUN_TEST(test_unorderedMap_insertPair);
    RUN_TEST(test_unorderedMap_insertAlreadyKeyToOverwriteValue);
    RUN_TEST(test_unorderedMap_insertPairsToTriggerResize);
    RUN_TEST(test_unorderedMap_insertPairsToTriggerMoreCollisionsOnRehashing);
    RUN_TEST(test_unorderedMap_insertPairsToTriggerMoreCollisionsOnRehashingCheckStructure);
    RUN_TEST(test_unordered_map_testFindNodesExistingOrNot);
    RUN_TEST(test_unordered_map_testEraseNodesExistingOrNot);

    return UNITY_END();
}