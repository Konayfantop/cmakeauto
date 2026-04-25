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

void test_tomlDecoding_findTheAutomakeConfigFileDirPath(void)
{
    chdir("test/automakeDirSimulation/randomFolder/innerFolder");

    char* result = getConfigFilePath();
    TEST_ASSERT_EQUAL_STRING(
        "/home/kostas/Documents/projects/CMakeAuto/test/automakeDirSimulation/.automake.toml", result);
}