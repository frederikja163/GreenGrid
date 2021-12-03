#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "CuTest.h"
#include "assertExtensions.h"
#include "isDataOutdated.h"

#define MAX_TIME_DIFF (10 * 60 * 60)

/* Test if the function returns 0 when MAX_TIME_DIFF is exceeded by recievingData. */
void test_outdated_data(CuTest *tc) {
    time_t curTime = time(NULL) - MAX_TIME_DIFF;
    struct tm * timeInfo = localtime(&curTime);
    char timeStr[15];

    assert_equal(strftime(timeStr, sizeof(timeStr), "%Y%m%d%H%M%S", timeInfo), sizeof(timeStr)-1);
    
    CuAssertTrue(tc, is_data_outdated(MAX_TIME_DIFF, timeStr));
}

/* Test if the function returns 1 when MAX_TIME_DIFF is not exceeded by recievingData. */
void test_not_outdated_data(CuTest *tc) {
    time_t curTime = time(NULL);
    struct tm * timeInfo = localtime(&curTime);
    char timeStr[15];

    assert_equal(strftime(timeStr, sizeof(timeStr), "%Y%m%d%H%M%S", timeInfo), sizeof(timeStr)-1);
    
    CuAssertTrue(tc, !is_data_outdated(MAX_TIME_DIFF, timeStr));
}

CuSuite *get_outdated_data_suite(void) {
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_outdated_data);
    SUITE_ADD_TEST(suite, test_not_outdated_data);

    return suite;
}