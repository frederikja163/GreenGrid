#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CuTest.h"
#include "calculateOptimalTime.h"



void test_optimal_time(CuTest *tc) {
    int activeHours = 3;
    windValue testArray[] = {
        {.timestamp = "20211125170000", .windspeed = 17.0},
        {.timestamp = "20211125180000", .windspeed = 29.2},
        {.timestamp = "20211125190000", .windspeed = 0.2},
        {.timestamp = "20211125200000", .windspeed = 20.0},
        {.timestamp = "20211125210000", .windspeed = 12.7},
        {.timestamp = "20211125220000", .windspeed = 7.0},
        {.timestamp = "20211125230000", .windspeed = 3.0},
        {.timestamp = "20211126000000", .windspeed = 8.4},
        {.timestamp = "20211126010000", .windspeed = 12.3},
        {.timestamp = "20211126020000", .windspeed = 20.8},
        {.timestamp = "20211126030000", .windspeed = 25.3},
        {.timestamp = "20211126040000", .windspeed = 0.0},
        {.timestamp = "20211126050000", .windspeed = 15.6},
        {.timestamp = "20211126060000", .windspeed = 10.2},
        {.timestamp = "20211126070000", .windspeed = 18.7}
    };

    int dataSize = sizeof(testArray) / sizeof(windValue);

    char *optimalTime = find_lowest_co2(activeHours, testArray, dataSize);

    CuAssertStrEquals(tc, testArray[12].timestamp, optimalTime);
}

void test_optimal_time2(CuTest *tc) {
    int activeHours = 3;
    windValue testArray[] = {
        {.timestamp = "20211125170000", .windspeed = 30},
        {.timestamp = "20211125180000", .windspeed = 30},
        {.timestamp = "20211125190000", .windspeed = 30},
        {.timestamp = "20211125200000", .windspeed = 30},
        {.timestamp = "20211125210000", .windspeed = 30},
        {.timestamp = "20211125220000", .windspeed = 30},
        {.timestamp = "20211125230000", .windspeed = 30},
        {.timestamp = "20211126000000", .windspeed = 30},
        {.timestamp = "20211126010000", .windspeed = 30},
        {.timestamp = "20211126020000", .windspeed = 30},
        {.timestamp = "20211126030000", .windspeed = 30},
        {.timestamp = "20211126040000", .windspeed = 30},
        {.timestamp = "20211126050000", .windspeed = 30},
        {.timestamp = "20211126060000", .windspeed = 30},
        {.timestamp = "20211126070000", .windspeed = 30}
    };

    int dataSize = sizeof(testArray) / sizeof(windValue);

    char *optimalTime = find_lowest_co2(activeHours, testArray, dataSize);

    CuAssertStrEquals(tc, testArray[0].timestamp, optimalTime);
}

void test_calculate_co2 (CuTest *tc) {
    double testvalue = calculate_co2(14.4);
    CuAssertDblEquals(tc, 10.6, testvalue, 0.1);
} 

CuSuite *calculate_optimal_time_suite(void) {
    CuSuite *suite = CuSuiteNew();    

    SUITE_ADD_TEST(suite, test_optimal_time);
    SUITE_ADD_TEST(suite, test_optimal_time2);
    SUITE_ADD_TEST(suite, test_calculate_co2);

    return suite;
}
