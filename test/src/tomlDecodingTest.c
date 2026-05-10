#include "unity.h"

#include "tomlDecoding.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void test_tomlDecoding_findProperlyTheContentsOfThePathWhenFoldersExist(void)
{
    chdir("test");

    char* result = getDirPathContent();
    TEST_ASSERT_EQUAL_STRING(".\n..\nautomakeDirSimulation\ndata\nsrc\n", result);
    free(result);
}

void test_tomlDecoding_findProperlyTheContentsOfThePathWhenFilesExist(void)
{
    chdir("test/automakeDirSimulation/randomFolder/innerFolder");

    char* result = getDirPathContent();
    TEST_ASSERT_EQUAL_STRING(".\n..\ngarbageFile.txt\n", result);
    free(result);
}

void test_tomlDecoding_notAbleTofindTheAutomakeConfigFileDirPath(void)
{
    chdir("test");

    char* result = getConfigFilePath();
    TEST_ASSERT_EQUAL_STRING(NULL, result);
}

// TODO : THIS TEST KILLS PORTABILITY , AND WE SHOULD AVOID USING LOCAL FOLDER NAME IN THE DIR PATH
void test_tomlDecoding_findTheAutomakeConfigFileDirPath(void)
{
    chdir("test/automakeDirSimulation/randomFolder/innerFolder");

    char* result = getConfigFilePath();
    TEST_ASSERT_EQUAL_STRING(
        "/home/kostas/Documents/projects/CMakeAuto/test/automakeDirSimulation/.automake.toml", result);
}

void test_tomlDecoding_decodeSimpleToml(void)
{
    chdir("test/data/inputExamplesToml/");
    unordered_mapT* unorderedMap = initUnorderedMap();
    const char* fullConfigPath = "simpleInput.toml";

    extractFields(&unorderedMap, fullConfigPath);

    TEST_ASSERT_EQUAL(18u, unorderedMap->size);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "name")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "version")->value, "0.0.0") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "language")->value, "C") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "type")->value, "Debug") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "standard")->value, "c11") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "output")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "level")->value, "z") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "lto")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "warnings")->value, "all") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "error")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "syntax")->value, "false") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "fatal")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "doubleFloatConv")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "shadow")->value, "local") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "danglingPtr")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "prefix")->value, "/usr/local") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "bin")->value, "bin/") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "logging")->value, "true") == 0);

    freeUnorderedMap(unorderedMap);
}

void test_tomlDecoding_decodeTomlFullOfCommentsOnThePairs(void)
{
    chdir("test/data/inputExamplesToml/");
    unordered_mapT* unorderedMap = initUnorderedMap();
    const char* fullConfigPath = "inputWithCommentsOnPairs.toml";

    extractFields(&unorderedMap, fullConfigPath);

    TEST_ASSERT_EQUAL(18u, unorderedMap->size);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "name")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "version")->value, "0.0.0") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "language")->value, "C") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "type")->value, "Debug") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "standard")->value, "c11") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "output")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "level")->value, "z") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "lto")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "warnings")->value, "all") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "error")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "syntax")->value, "false") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "fatal")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "doubleFloatConv")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "shadow")->value, "local") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "danglingPtr")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "prefix")->value, "/usr/local") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "bin")->value, "bin/") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "logging")->value, "true") == 0);

    freeUnorderedMap(unorderedMap);
}

void test_tomlDecoding_decodeTomlFullOfCommentsWherever(void)
{
    chdir("test/data/inputExamplesToml/");
    unordered_mapT* unorderedMap = initUnorderedMap();
    const char* fullConfigPath = "inputWithCommentsWherever.toml";

    extractFields(&unorderedMap, fullConfigPath);

    TEST_ASSERT_EQUAL(18u, unorderedMap->size);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "name")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "version")->value, "0.0.0") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "language")->value, "C") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "type")->value, "Debug") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "standard")->value, "c11") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "output")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "level")->value, "z") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "lto")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "warnings")->value, "all") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "error")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "syntax")->value, "false") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "fatal")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "doubleFloatConv")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "shadow")->value, "local") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "danglingPtr")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "prefix")->value, "/usr/local") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "bin")->value, "bin/") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "logging")->value, "true") == 0);

    freeUnorderedMap(unorderedMap);
}

void test_tomlDecoding_decodeTomlFullOfCommentsWhereverButWithoutEmptyLineInTheEnd(void)
{
    chdir("test/data/inputExamplesToml/");
    unordered_mapT* unorderedMap = initUnorderedMap();
    const char* fullConfigPath = "inputWithCommentsWhereverWithoutNextLineInTheEnd.toml";

    extractFields(&unorderedMap, fullConfigPath);

    TEST_ASSERT_EQUAL(18u, unorderedMap->size);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "name")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "version")->value, "0.0.0") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "language")->value, "C") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "type")->value, "Debug") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "standard")->value, "c11") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "output")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "level")->value, "z") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "lto")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "warnings")->value, "all") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "error")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "syntax")->value, "false") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "fatal")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "doubleFloatConv")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "shadow")->value, "local") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "danglingPtr")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "prefix")->value, "/usr/local") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "bin")->value, "bin/") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "logging")->value, "true") == 0);

    freeUnorderedMap(unorderedMap);
}

void test_tomlDecoding_decodeTomlFullOfCommentsButWithHeaderInTheEndWithoutValues(void)
{
    chdir("test/data/inputExamplesToml/");
    unordered_mapT* unorderedMap = initUnorderedMap();
    const char* fullConfigPath = "inputWithLastHeaderButNoValues.toml";

    extractFields(&unorderedMap, fullConfigPath);

    TEST_ASSERT_EQUAL(18u, unorderedMap->size);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "name")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "version")->value, "0.0.0") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "language")->value, "C") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "type")->value, "Debug") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "standard")->value, "c11") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "output")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "level")->value, "z") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "lto")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "warnings")->value, "all") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "error")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "syntax")->value, "false") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "fatal")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "doubleFloatConv")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "shadow")->value, "local") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "danglingPtr")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "prefix")->value, "/usr/local") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "bin")->value, "bin/") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "logging")->value, "true") == 0);

    freeUnorderedMap(unorderedMap);
}

// We want best effort and so we do
void test_tomlDecoding_decodeTomlsimpleInputButKeysWithoutValue(void)
{
    chdir("test/data/inputExamplesToml/");
    unordered_mapT* unorderedMap = initUnorderedMap();
    const char* fullConfigPath = "simpleInputButKeysWithoutValue.toml";

    extractFields(&unorderedMap, fullConfigPath);

    TEST_ASSERT_EQUAL(16u, unorderedMap->size);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "name")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "version")->value, "0.0.0") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "language")->value, "C") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "type")->value, "Debug") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "standard")->value, "c11") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "output")->value, "automake") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "level")->value, "z") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "lto")->value, "true") == 0);
    TEST_ASSERT_TRUE(find(unorderedMap, "warnings") == NULL);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "error")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "syntax")->value, "false") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "fatal")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "doubleFloatConv")->value, "true") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "shadow")->value, "local") == 0);
    TEST_ASSERT_TRUE(find(unorderedMap, "danglingPtr") == NULL);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "prefix")->value, "/usr/local") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "bin")->value, "bin/") == 0);
    TEST_ASSERT_TRUE(strcmp(find(unorderedMap, "logging")->value, "true") == 0);

    freeUnorderedMap(unorderedMap);
}



