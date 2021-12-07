#include "fileIO.h"
/* To force files to use LF files endings if using any Windows OS */
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assertExtensions.h"

char *read_file(const char *fileName) {
    FILE *inputFilePtr;
    char *fileContents;
    size_t fileSize = 0;
    size_t readSize;

    assert_not_equal(inputFilePtr = fopen(fileName, "r"), NULL);

    fseek(inputFilePtr, 0, SEEK_END);
    fileSize = ftell(inputFilePtr);
    fseek(inputFilePtr, 0, SEEK_SET);

    assert_not_equal(fileContents = malloc((fileSize + 1) * sizeof(char)), NULL);

    assert_equal(readSize = fread(fileContents, sizeof(char), fileSize, inputFilePtr), fileSize);

    fileContents[fileSize] = '\0';

#ifdef _WIN32
    _setmode(_fileno(inputFilePtr), _O_BINARY);
#endif
    fclose(inputFilePtr);

    return fileContents;
}

void write_file(const char *fileName, const char *fileContents) {
    FILE *outputFilePtr;
    size_t fileSize = strlen(fileContents);

    assert_not_equal(outputFilePtr = fopen(fileName, "w+"), NULL);

    fputs(fileContents, outputFilePtr);

#ifdef _WIN32
    _setmode(_fileno(outputFilePtr), _O_BINARY);
#endif
    fclose(outputFilePtr);
}