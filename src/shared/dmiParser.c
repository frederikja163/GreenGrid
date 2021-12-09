#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cJSON.h>
#include <assert.h>
#include "dmiParser.h"

/*input ninjo2dnudk.json and you will get out an array of windValues and a timestamp for last update*/
windValue* load_wind_data(const char *input, char **lastUpdate)
{
    cJSON *json = cJSON_Parse(input);
    if (json == NULL)
    {
        const char *error = cJSON_GetErrorPtr();
        if (error != NULL)
        {
            fprintf(stderr, "Error at: %s", error);
        }
        return 0;
    }
    assert(json != NULL);
    get_last_update_from_json(json, &*lastUpdate);
    assert(*lastUpdate != NULL);
    windValue *values = get_all_wind_values(json);
    assert(values != NULL);
    cJSON_Delete(json);

    return values;
}

void get_last_update_from_json(cJSON *json, char **lastUpdate)
{
    cJSON *lastUpdateJson = cJSON_GetObjectItem(json, "lastupdate");
    if (!(cJSON_IsString(lastUpdateJson) && lastUpdateJson->valuestring != NULL))
        return;
    int strLen = strlen(lastUpdateJson->valuestring);
    *lastUpdate = (char*) malloc((strLen + 1) * sizeof(char));
    strcpy(*lastUpdate, lastUpdateJson->valuestring);
}

windValue* get_all_wind_values(cJSON *json)
{
    windValue *values = (windValue*) malloc(97 * sizeof(windValue)); /*timeserie of size 97*/
    if (values == NULL)
        return NULL;

    int iterator = 0;
    cJSON *timeserie = cJSON_GetObjectItem(json, "timeserie");
    if (!cJSON_IsArray(timeserie))
        return NULL;

    cJSON *hour;
    cJSON_ArrayForEach(hour, timeserie)
    {
        cJSON *time = cJSON_GetObjectItem(hour, "time");
        cJSON *windSpeed = cJSON_GetObjectItem(hour, "windSpeed");
        if (!cJSON_IsString(time) || !cJSON_IsNumber(windSpeed))
        {
            continue;
        }
        values[iterator].windspeed = windSpeed->valuedouble;
        values[iterator].timestamp = (char*) calloc(15, sizeof(char));
        strcpy(values[iterator].timestamp, time->valuestring);
        iterator++;
    }
    return values;
}

