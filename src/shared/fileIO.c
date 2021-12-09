#include "fileIO.h"

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assertExtensions.h"

char *read_file(const char *filePath) {
    FILE *inputFilePtr;
    char *fileContents;
    size_t fileSize = 0;
    size_t readSize;

    /* Open stream to filePath in read mode */
    assert_not_equal(inputFilePtr = fopen(filePath, "r"), NULL);

    /* Get size of file in bytes */
    fseek(inputFilePtr, 0, SEEK_END);
    fileSize = ftell(inputFilePtr);
    fseek(inputFilePtr, 0, SEEK_SET);

    assert_not_equal(fileContents = malloc((fileSize + 1) * sizeof(char)), NULL);

    /* Read everything in file to fileContents */
    assert_equal(readSize = fread(fileContents, sizeof(char), fileSize, inputFilePtr), fileSize);

    /* Convert char array to null terminated string */
    fileContents[fileSize] = '\0';

/* Force files to use LF files endings if using any Windows OS */
#ifdef _WIN32
    _setmode(_fileno(inputFilePtr), _O_BINARY);
#endif
    /* Close stream to filePath */
    fclose(inputFilePtr);

    return fileContents;
}

void write_file(const char *filePath, const char *fileContents) {
    FILE *outputFilePtr;

    /* Open stream to filePath in write mode */
    assert_not_equal(outputFilePtr = fopen(filePath, "w+"), NULL);

    /* fileContents is written into the file */
    fputs(fileContents, outputFilePtr);

#ifdef _WIN32
    _setmode(_fileno(outputFilePtr), _O_BINARY);
#endif
    fclose(outputFilePtr);
}