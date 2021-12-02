#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

#include <string.h>

#include "CuTest.h"
#include "assertExtensions.h"
#include "fileIO.h"

#define TEST_STRING "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nMorbi dignissim nunc vel lectus egestas, nec rutrum nibh gravida.\n\t(){}[];:<>\\\"'"

/* Test to check that contents of a file are the same as a string read from the same file */
void test_read_write_roundtrip(CuTest *tc) {
    const char *string = TEST_STRING;
    char *read_string;

    write_file("src/tests/testString.tmp", string);
    read_string = read_file("src/tests/testString.tmp");

    CuAssertStrEquals(tc, string, read_string);

    free(read_string);
}

/* Test to check that a file is created on the specified path */
void test_write_file_exists(CuTest *tc) {
    const char *string = TEST_STRING;
    FILE *filePtr;

    write_file("src/tests/testString2.tmp", string);
    CuAssertTrue(tc, (filePtr = fopen("src/tests/testString2.tmp", "r")) != NULL);

    fclose(filePtr);
}

/* Test to check that the size of a new written file is equal to the size of a string read from the same file */
void test_write_file_size(CuTest *tc) {
    FILE *filePtr;
    const char string[] = TEST_STRING;

    write_file("src/tests/testString3.tmp", string);

    assert_not_equal(filePtr = fopen("src/tests/testString3.tmp", "r"), NULL);

    fseek(filePtr, 0, SEEK_END);
    const size_t fileSize = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    CuAssertTrue(tc, fileSize == strlen(string));

#ifdef _WIN32
    _setmode(_fileno(filePtr), _O_BINARY);
#endif
    fclose(filePtr);
}

/* Test to check that the size of a read file is equal to the size of a string read from the same file */
void test_read_string_size(CuTest *tc) {
    FILE *filePtr;
    char *read_string;
    const char string[] = TEST_STRING;
    size_t fileSize, readSize;

    write_file("src/tests/testString4.tmp", string);

    assert_not_equal(filePtr = fopen("src/tests/testString4.tmp", "r"), NULL);

    fseek(filePtr, 0, SEEK_END);
    fileSize = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    assert_not_equal(read_string = malloc((fileSize + 1) * sizeof(char)), NULL);

#ifdef _WIN32
    _setmode(_fileno(filePtr), _O_BINARY);
#endif
    readSize = fread(read_string, sizeof(char), fileSize, filePtr);

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
