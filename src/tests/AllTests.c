#include <stdio.h>

#include "CuTest.h"

CuSuite *get_file_io_suite(void);
CuSuite *dmi_parser_suite(void);

int run_all_tests(void) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, get_file_io_suite());
    CuSuiteAddSuite(suite, dmi_parser_suite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    return suite->failCount;
}

int main(void) {
    return run_all_tests();
}