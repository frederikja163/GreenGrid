#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "CuTest.h"
#include "assertExtensions.h"
#include "timestamp.h"

/* Test if the current timestamp can be parased as a timestamp to a tm struct. */
void test_parse_current_timestamp(CuTest *tc) {
    time_t curTime = time(NULL);
    struct tm *timeInfo = localtime(&curTime);
    char timeStamp[15];

    strftime(timeStamp, sizeof(timeStamp), "%Y%m%d%H%M%S", timeInfo);

    struct tm testTime = timestamp_to_tm(timeStamp);
    CuAssertIntEquals(tc, timeInfo->tm_sec, testTime.tm_sec);
    CuAssertIntEquals(tc, timeInfo->tm_min, testTime.tm_min);
    CuAssertIntEquals(tc, timeInfo->tm_hour, testTime.tm_hour);
    CuAssertIntEquals(tc, timeInfo->tm_mday, testTime.tm_mday);
    CuAssertIntEquals(tc, timeInfo->tm_mon, testTime.tm_mon);
    CuAssertIntEquals(tc, timeInfo->tm_year, testTime.tm_year);
    /* CuAssertIntEquals(tc, timeInfo->tm_wday, testTime.tm_wday); /* We dont care about weekdays. */
    /* CuAssertIntEquals(tc, timeInfo->tm_yday, testTime.tm_yday); /* We dont care about yeardays. */
    /* CuAssertIntEquals(tc, timeInfo->tm_isdst, testTime.tm_isdst); /* We dont care about DST */
}

/* Test the time difference function. */
void test_time_difference(CuTest *tc) {
    time_t curTime = time(NULL) - 60 * 60 * 1; /* One hour ago. */
    struct tm *timeInfo = localtime(&curTime);
    char timeStamp[15];

    assert_equal(strftime(timeStamp, sizeof(timeStamp), "%Y%m%d%H%M%S", timeInfo), sizeof(timeStamp) - 1);

    CuAssertIntEquals(tc, get_time_difference(timeStamp), 1);
}

CuSuite *get_timestamp_suite(void) {
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_parse_current_timestamp);
    SUITE_ADD_TEST(suite, test_time_difference);

    return suite;
}