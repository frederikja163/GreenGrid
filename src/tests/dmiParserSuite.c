#include <stdio.h>
#include <cJSON.h>
#include <string.h>
#include "CuTest.h"
#include "dmiParser.h"
#include "fileIO.h"

void test_cjson_parse(CuTest *tc)
{
    char *inputString = read_file("data/ninjo2dmidk.json");
    cJSON *json = cJSON_Parse(inputString);

    if (json == NULL)
    {
        const char *error = cJSON_GetErrorPtr();
        if (error != NULL)
            CuAssert(tc, error, 0);
        else
            CuAssertTrue(tc, 0);
    }
}

void test_read_of_last_updated(CuTest *tc)
{
    char *inputString = read_file("data/ninjo2dmidk.json");

    cJSON *json = cJSON_Parse(inputString);
    cJSON *lastUpdateJson = cJSON_GetObjectItem(json, "lastupdate");
    CuAssertTrue(tc, cJSON_IsString(lastUpdateJson) && (lastUpdateJson->valuestring != NULL));
    char* lastUpdated;
    get_last_update_from_json(json, &lastUpdated);
    CuAssertTrue(tc, lastUpdated != NULL);

    cJSON_Delete(json);
    free(inputString);
    free(lastUpdated);
}

void test_read_whole_json(CuTest *tc)
{
    char *input = read_file("data/ninjo2dmidk.json");
    char *lastUpdated;
    windValue* windValues = load_wind_data(input, &lastUpdated);

    CuAssertTrue(tc, lastUpdated != NULL);
    int i;
    for (i = 0; i < 53; i++) {
        CuAssertTrue(tc, windValues[i].timestamp != NULL);
    }

    for (i = 0; i < 53; ++i) {
        free(windValues[i].timestamp);
    }
    free(windValues);
    free(input);
}

CuSuite *dmi_parser_suite(void) {
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_cjson_parse);
    SUITE_ADD_TEST(suite, test_read_of_last_updated);
    SUITE_ADD_TEST(suite, test_read_whole_json);

    return suite;
}
