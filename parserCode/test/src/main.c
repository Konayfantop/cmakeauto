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

void test_tomlDecoding_findProperlyTheContentsOfThePathWhenFoldersExist(void);
void test_tomlDecoding_findProperlyTheContentsOfThePathWhenFilesExist(void);
void test_tomlDecoding_notAbleTofindTheAutomakeConfigFileDirPath(void);
void test_tomlDecoding_findTheAutomakeConfigFileDirPath(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_tomlDecoding_findProperlyTheContentsOfThePathWhenFoldersExist);
    RUN_TEST(test_tomlDecoding_findProperlyTheContentsOfThePathWhenFilesExist);
    RUN_TEST(test_tomlDecoding_notAbleTofindTheAutomakeConfigFileDirPath);
    RUN_TEST(test_tomlDecoding_findTheAutomakeConfigFileDirPath);

    return UNITY_END();
}