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

    if ((inputFilePtr = fopen(fileName, "r")) == NULL) {
        fprintf(stderr, "Error : could not open file");
        exit(EXIT_FAILURE);
    }

    fseek(inputFilePtr, 0, SEEK_END);
    fileSize = ftell(inputFilePtr);
    fseek(inputFilePtr, 0, SEEK_SET);

    if ((fileContents = malloc((fileSize + 1) * sizeof(char))) == NULL) {
        fprintf(stderr, "Error : could not allocate memory");
        exit(EXIT_FAILURE);
    }

    if ((readSize = fread(fileContents, sizeof(char), fileSize, inputFilePtr)) != fileSize) {
        printf("\n%zu != %zu\n", readSize, fileSize);
        fprintf(stderr, "Error : could not read file to string");
        exit(EXIT_FAILURE);
    }

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

    if ((outputFilePtr = fopen(fileName, "w+")) == NULL) {
        fprintf(stderr, "Error : could not open file");
        exit(EXIT_FAILURE);
    }
    fputs(fileContents, outputFilePtr);

#ifdef _WIN32
    _setmode(_fileno(outputFilePtr), _O_BINARY);
#endif
    fclose(outputFilePtr);
}