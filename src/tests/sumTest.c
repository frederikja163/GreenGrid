#include "CuTest.h"
#include "sum.h"

void test_sum(CuTest* tc) {
    CuAssertTrue(tc, sum(5, 4) == 9);
    CuAssertTrue(tc, sum(0, 0) == 0);
    CuAssertTrue(tc, sum(-5, -4) == -9);
    CuAssertTrue(tc, sum(5, -4) == 1);
}

CuSuite* get_sum_suite(void) {
	CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_sum);

    return suite;
}