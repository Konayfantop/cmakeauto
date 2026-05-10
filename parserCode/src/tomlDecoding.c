#include "tomlDecoding.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "commonDecl.h"
#include <colorLogging.h>

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

void extractFields(unordered_mapT** unorderedMap, const char* const configDirPath)
{
    FILE* f = fopen(configDirPath, "rb");
    if(f == NULL)
    {
        MAKE_ERROR("Not able to open the file, even though we managed to locate it");
        return;
    }

    fseek(f, 0, SEEK_END);
    long long fileSize = ftell(f);
    rewind(f);
    char* fileBuffer = (char *)malloc( (fileSize+1) * sizeof(char) );
    char* toFreeLater = fileBuffer;

    if(fileBuffer == NULL)
    {
        MAKE_ERROR("Not enough memory for buffer transfering of conf file data");
        fclose(f);
        return;
    }
    const size_t lastPos = fread(fileBuffer, 1, fileSize, f);
    if(lastPos != (size_t)fileSize)
    {
        MAKE_ERROR("WARNING: partial read");
    }
    fileBuffer[lastPos] = '\0';
    fclose(f);

    while(*fileBuffer != '\0')
    {
        if(*fileBuffer == ' ' || *fileBuffer == '\n' || *fileBuffer == ']')
        {
            ++fileBuffer;
        }
        else if(*fileBuffer == '[')
        {
            while(*fileBuffer != ']')
            {
                ++fileBuffer;
            }
        }
        else if(*fileBuffer == '#')
        {
            while(*fileBuffer != '\n' && *fileBuffer != '\0')
            {
                ++fileBuffer;
            }
        }
        else if( (*fileBuffer >= 'a' && *fileBuffer <= 'z') || (*fileBuffer >= 'A' && *fileBuffer <= 'Z') )
        {
            char* keyCursor = fileBuffer;
            while( (*keyCursor >= 'a' && *keyCursor <= 'z') || (*keyCursor >= 'A' && *keyCursor <= 'Z') ) // when ' ' or '=' we stop
            {
                ++keyCursor;
            }

            char* startValueCursor = keyCursor;
            while(*startValueCursor == ' ' || *startValueCursor == '=' || *startValueCursor == '\"')
            {
                ++startValueCursor;
            }

            char* endValueCursor = startValueCursor;
            while(*endValueCursor != '\"' && *endValueCursor != '\n')
            {
                ++endValueCursor;
            }

            const size_t keyLength = keyCursor-fileBuffer;
            const size_t valueLength = endValueCursor-startValueCursor;

            char* key = (char *)malloc((keyLength+1) * sizeof(char));
            char* value = (char *)malloc((valueLength+1) * sizeof(char));
            
            memcpy(key, fileBuffer, keyCursor-fileBuffer+1);
            key[keyLength] = '\0';
            memcpy(value, startValueCursor, endValueCursor-startValueCursor+1);
            value[valueLength] = '\0';

            insert(unorderedMap, key, value);

            fileBuffer = endValueCursor+1;
        }
    }

    free(toFreeLater);
}

unsigned int parseTomlIfExists()
{
    char* configDirPath = getConfigFilePath();
    if(configDirPath == NULL)
    {
        return 0;
    }

    unordered_mapT* unorderedMap = initUnorderedMap();
    if(unorderedMap == NULL)
    {
        MAKE_ERROR("Memory problem occured during decoding / preparation. No config file is taken into account");
        free(configDirPath);
        return 0;
    }

    // reference of the unorderedMap in case of rehashing
    extractFields(&unorderedMap, configDirPath);

    free(configDirPath);
    return 1;
}