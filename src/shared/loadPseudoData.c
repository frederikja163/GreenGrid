#include "loadPseudoData.h"

#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *fileName) {
    FILE *inputFilePtr;
    char *fileContents;
    size_t fileSize = 0;

    if ((inputFilePtr = fopen(fileName, "r")) == NULL) {
        fprintf(stderr, "Error : Unable to open %s for reading\n", fileName);
        exit(EXIT_FAILURE);
    }

    fseek(inputFilePtr, 0, SEEK_END);
    fileSize = ftell(inputFilePtr);
    fseek(inputFilePtr, 0, SEEK_SET);

    fileContents = malloc((fileSize + 1) * sizeof(char));
    if (fileContents == NULL) {
        fprintf(stderr, "Error : Unable to allocate memory.\n");
        fclose(inputFilePtr);
        exit(EXIT_FAILURE);
    }

    if (fread(fileContents, sizeof(char), fileSize, inputFilePtr) < fileSize) {
        fprintf(stderr, "Error : Unable to read file to string.\n");
        fclose(inputFilePtr);
        free(fileContents);
        exit(EXIT_FAILURE);
    }

    fileContents[fileSize] = '\0';

    fclose(inputFilePtr);

    return fileContents;
}

void write_file(const char *fileName, const char *fileContents) {
    FILE *outputFilePtr;
    if ((outputFilePtr = fopen(fileName, "w+")) == NULL) {
        fprintf(stderr, "Error : Unable to open %s for writing\n", fileName);
        exit(EXIT_FAILURE);
    }

    fputs(fileContents, outputFilePtr);

    fclose(outputFilePtr);
}