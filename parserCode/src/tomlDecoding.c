#include "tomlDecoding.h"

#include "commonDecl.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char* getDirPathContent()
{
    static const int kDirPathExploreSize = 100;
    static const int kExploreDirectorySize = 5000;

    FILE* pipelinePtr = popen("ls -a", "r");
    if(pipelinePtr == NULL)
    {
        MAKE_WARN("Not able to explore or open the terminal pipeline, no file found, creating a default instead");
        return NULL;
    }

    char path[kDirPathExploreSize];
    char result[kExploreDirectorySize];
    while (fgets(path, sizeof(path), pipelinePtr) != NULL)
    {
        strcat(result, path);
    }

    pclose(pipelinePtr);

    return result;
}

char* openFileIfExists()
{
    static const char* kConfigFolderName = ".automake";
    static const char* kConfigFileName = "automakerc.toml";

    char rcFilePath[100];

    while(1)
    {
        getcwd(rcFilePath, sizeof(rcFilePath));
        if(rcFilePath == NULL)
        {
            MAKE_WARN("Not able to fetch the absolute path, no file found, creating a default instead");
            return NULL;
        }
        if(strcmp(rcFilePath, "/") == 0)
        {
            MAKE_WARN("No %s config folder found, creating a default instead", kConfigFolderName);
            return NULL;
        }

        char* currentDirContent = getDirPathContent();
        
        if (strstr(currentDirContent, kConfigFolderName) != NULL && chdir(kConfigFolderName))
        {
            char* nestedResult = getDirPathContent();
            if(strstr(nestedResult, kConfigFileName) != NULL)
            {
                getcwd(rcFilePath, sizeof(rcFilePath));

                MAKE_DEBUG("Found the config file in the path : %s", rcFilePath);
                return rcFilePath;
            }
        }
        else
        {
            chdir("..");
        }
    }
    return NULL;
}

unsigned int parseTomlIfExists()
{
    const char* configDirPath = openFileIfExists();
    if(configDirPath == NULL)
    {
        return 0;
    }

    return 1;
}