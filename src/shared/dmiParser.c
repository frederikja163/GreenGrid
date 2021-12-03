#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cJSON.h>
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
            printf("Error at: %s", error);
        }
        return 0;
    }

    cJSON *lastUpdateJson = cJSON_GetObjectItem(json, "lastupdate");
    if (cJSON_IsString(lastUpdateJson) && (lastUpdateJson->valuestring != NULL))
    {
        int strLen = strlen(lastUpdateJson->valuestring);
        *lastUpdate = malloc((strLen + 1) * sizeof(char));
        if (*lastUpdate == NULL) {
            return 0;
        }
        strcpy(*lastUpdate, lastUpdateJson->valuestring);
        /*printf("Input file last updated: %s\n", *lastUpdate);*/
    }
    else
        printf("Failed to get timestamp for last updated\n");
    
    windValue *values = (windValue*) calloc(97, sizeof(windValue)); /*timeserie of size 97*/
    if(values == NULL)
        return 0;  /* out of memory! */
    
    int iterator = 0;
    cJSON *timeserie = cJSON_GetObjectItem(json, "timeserie");
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
        values[iterator].timestamp = (char*) calloc(20, sizeof(char));
        strcpy(values[iterator].timestamp, time->valuestring);
        iterator++;
    }
    cJSON_Delete(json);

    return values;
}
