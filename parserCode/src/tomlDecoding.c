#include "tomlDecoding.h"

#include "commonDecl.h"
#include <colorLogging.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char* getDirPathContent()
{
    static const int kDirPathExploreSize = 1000;
    static const int kExploreDirectorySize = 5000;

    FILE* pipelinePtr = popen("ls -a", "r");
    if(pipelinePtr == NULL)
    {
        MAKE_WARNING("Not able to explore or open the terminal pipeline, no file found, creating a default instead");
        pclose(pipelinePtr);
        return NULL;
    }

    char path[kDirPathExploreSize];
    char* result = (char *)malloc(sizeof(char) * kExploreDirectorySize);
    if(result == NULL)
    {
        pclose(pipelinePtr);
        MAKE_WARNING("Not able to allocate memory, is a process running consuming everything ? creating a default instead");
        return NULL;
    }

    result[0] = '\0';
    while (fgets(path, kDirPathExploreSize, pipelinePtr) != NULL)
    {
        strcat(result, path);
    }

    pclose(pipelinePtr);

    return result;
}

char* getConfigFilePath()
{
    static const char* kConfigFolderName = ".automake";
    static const char* kConfigFileName = "automakerc.toml";

    char* rcFilePath = (char *)malloc(sizeof(char) * 5000);
    char* currentDirContent;

    while(1)
    {
        getcwd(rcFilePath, 5000);

        if(rcFilePath == NULL)
        {
            MAKE_WARNING("Not able to fetch the absolute path, no file found, creating a default instead");
            break;
        }
        if(strcmp(rcFilePath, "/") == 0)
        {
            MAKE_WARNING("No config folder found, creating a default instead");
            break;
        }

        currentDirContent = getDirPathContent();

        if (strstr(currentDirContent, kConfigFolderName) != NULL)
        {
            chdir(kConfigFolderName);

            char* nestedResult = getDirPathContent();

            if(strstr(nestedResult, kConfigFileName) != NULL)
            {
                getcwd(rcFilePath, 5000);

                MAKE_DEBUG("Found the config file");

                free(currentDirContent);
                strcat(rcFilePath, ".toml");
                return rcFilePath;
            }
        }
        else
        {
            chdir("..");
        }
    }

    free(currentDirContent);
    return NULL;
}

unsigned int parseTomlIfExists()
{
    const char* configDirPath = getConfigFilePath();
    if(configDirPath == NULL)
    {
        return 0;
    }

    

    return 1;
}