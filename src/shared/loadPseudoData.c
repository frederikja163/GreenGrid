#include "loadPseudoData.h"

#include <stdio.h>
#include <stdlib.h>

#include "assertExtensions.h"

char *read_file(const char *fileName) {
    FILE *inputFilePtr;
    char *fileContents;
    size_t fileSize = 0;

    assert_not_equal(inputFilePtr = fopen(fileName, "r"), NULL);

    fseek(inputFilePtr, 0, SEEK_END);
    fileSize = ftell(inputFilePtr);
    fseek(inputFilePtr, 0, SEEK_SET);

    assert_not_equal(fileContents = malloc((fileSize + 1) * sizeof(char)), NULL);

    assert_equal(fread(fileContents, sizeof(char), fileSize, inputFilePtr), fileSize);

    fileContents[fileSize] = '\0';

    fclose(inputFilePtr);

    return fileContents;
}

void write_file(const char *fileName, const char *fileContents) {
    FILE *outputFilePtr;
    assert_not_equal(outputFilePtr = fopen(fileName, "w+"), NULL);

    fputs(fileContents, outputFilePtr);

    fclose(outputFilePtr);
}