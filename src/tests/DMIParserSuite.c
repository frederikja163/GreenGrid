#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cJSON.h>
#include "CuTest.h"
#include "assertExtensions.h"
#include "DMIParser.h"
/*
void CuAssert(CuTest* tc, char* message, int condition);
void CuAssertTrue(CuTest* tc, int condition);
void CuAssertStrEquals(CuTest* tc, char* expected, char* actual);
void CuAssertIntEquals(CuTest* tc, int expected, int actual);
void CuAssertPtrEquals(CuTest* tc, void* expected, void* actual);
void CuAssertPtrNotNull(CuTest* tc, void* pointer);
 */
/*TODO: fix so that these code snippets refer to functions instead of snippets of code from DMIParser*/
void TestCJSONParse(CuTest *tc)
{
    cJSON *json = cJSON_Parse(input);
    if (json == NULL)
    {
        const char *error = cJSON_GetErrorPtr();
        if (error != NULL)
        {
            printf("Error at: %s", error);
        }
        return 0;
    }
}
void TestReadOfLastUpdated(CuTest *tc)
{
    cJSON *lastUpdateJson = cJSON_GetObjectItem(json, "lastupdate");
    if (cJSON_IsString(lastUpdateJson) && (lastUpdateJson->valuestring != NULL))
    {
        lastUpdate = lastUpdateJson->valuestring;
        /*printf("Input file last updated: %s\n", lastUpdate);*/
    }
    else
        printf("Failed to get timestamp for last updated\n");
}
void TestReadWholeJSon(CuTest *tc)
{
    char *input = read_file("src/shared/ninjo2dmidk.json");
    char *lastUpdate;
    windValue* windValues = ParseStringToWind(input, lastUpdate);
    //assert both lastupdate and windvalue are not null
}
/*Adds test functions*/
CuSuite *DMIParser_suite(void) {
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestCJSONParse);
    SUITE_ADD_TEST(suite, TestReadOfLastUpdated);
    SUITE_ADD_TEST(suite, TestReadWholeJSon);

    return suite;
}