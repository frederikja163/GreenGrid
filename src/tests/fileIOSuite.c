#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

#include <string.h>

#include "CuTest.h"
#include "fileIO.h"

#define TEST_STRING "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nMorbi dignissim nunc vel lectus egestas, nec rutrum nibh gravida.\n\t(){}[];:<>\\\"'"

/* When writing to a file and reading the file to a string, it should be the same */
/* When writing a file, a file should be at the specified path */
/* The file size should equate to the size of the string */
/* When reading a file, the string size should equate to the file size */

void test_read_write_roundtrip(CuTest *tc) {
    const char *string = TEST_STRING;
    char *read_string;

    write_file("src/tests/testString.tmp", string);
    read_string = read_file("src/tests/testString.tmp");

    CuAssertStrEquals(tc, string, read_string);

    free(read_string);
}

void test_write_file_exists(CuTest *tc) {
    const char *string = TEST_STRING;
    FILE *filePtr;

    write_file("src/tests/testString2.tmp", string);
    CuAssertTrue(tc, (filePtr = fopen("src/tests/testString2.tmp", "r")) != NULL);

    fclose(filePtr);
}

void test_write_file_size(CuTest *tc) {
    FILE *filePtr;
    const char string[] = TEST_STRING;

    write_file("src/tests/testString3.tmp", string);

#ifdef _WIN32
    _setmode(_fileno(filePtr), _O_BINARY);
#endif
    if ((filePtr = fopen("src/tests/testString3.tmp", "r")) == NULL) {
        fprintf(stderr, "Error : could not open file");
        exit(EXIT_FAILURE);
    }

    fseek(filePtr, 0, SEEK_END);
    const size_t fileSize = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    CuAssertTrue(tc, fileSize == strlen(string));

#ifdef _WIN32
    _setmode(_fileno(filePtr), _O_BINARY);
#endif
    fclose(filePtr);
}

void test_read_string_size(CuTest *tc) {
    FILE *filePtr;
    char *read_string;
    size_t fileSize, readSize;

    if ((filePtr = fopen("src/tests/testString3.tmp", "r")) == NULL) {
        fprintf(stderr, "Error : could not open file");
        exit(EXIT_FAILURE);
    }

    fseek(filePtr, 0, SEEK_END);
    fileSize = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    if ((read_string = malloc((fileSize + 1) * sizeof(char))) == NULL) {
        fprintf(stderr, "Error : could not allocate memory");
        exit(EXIT_FAILURE);
    }

#ifdef _WIN32
    _setmode(_fileno(filePtr), _O_BINARY);
#endif
    if ((readSize = fread(read_string, sizeof(char), fileSize, filePtr)) != fileSize) {
        printf("\n%zu != %zu\n", readSize, fileSize);
        fprintf(stderr, "Error : could not read file to string");
        exit(EXIT_FAILURE);
    }

    CuAssertTrue(tc, readSize == fileSize);

    fclose(filePtr);
    free(read_string);
}

CuSuite *get_file_io_suite(void) {
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_read_write_roundtrip);
    SUITE_ADD_TEST(suite, test_write_file_exists);
    SUITE_ADD_TEST(suite, test_write_file_size);
    SUITE_ADD_TEST(suite, test_read_string_size);

    return suite;
}
