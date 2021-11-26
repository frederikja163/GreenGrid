#include "loadPseudoData.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *fileName) {
    FILE *inputFilePtr;
    char *fileContents;
    size_t fileSize = 0;

    assert((inputFilePtr = fopen(fileName, "r")) != NULL);

    fseek(inputFilePtr, 0, SEEK_END);
    fileSize = ftell(inputFilePtr);
    fseek(inputFilePtr, 0, SEEK_SET);

    assert((fileContents = malloc((fileSize + 1) * sizeof(char))) != NULL);

    assert(fread(fileContents, sizeof(char), fileSize, inputFilePtr) == fileSize);

    fileContents[fileSize] = '\0';

    fclose(inputFilePtr);

    return fileContents;
}

void write_file(const char *fileName, const char *fileContents) {
    FILE *outputFilePtr;
    assert((outputFilePtr = fopen(fileName, "w+")) != NULL);

    fputs(fileContents, outputFilePtr);

    fclose(outputFilePtr);
}