/*
 * Created by Aavild on 19/11/2021.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cJSON.h>
#include "DMIParser.h"
/*#include <curl/curl.h>*/

/*input ninjo2dnudk.json and you will get out an array of windValues and a timestamp for last update*/
windValue* ParseStringToWind(const char *input, char *lastUpdate)
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
        lastUpdate = lastUpdateJson->valuestring;
        printf("Input file last updated: %s\n", lastUpdate);
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
        /*printf("windspeed: %lf - ", windSpeed->valuedouble);
        printf("time: %s ", time->valuestring);*/
        values[iterator].windspeed = windSpeed->valuedouble;
        values[iterator].timestamp = (char*) calloc(20, sizeof(char));
        strcpy(values[iterator].timestamp, time->valuestring);
        iterator++;
    }
    cJSON_Delete(json);
    return values;
}
/* Working main for this
int main(int argc, char **argv) {
    char *inputString;
    inputString = read_file("src/shared/ninjo2dmidk.json");
    char *updateTimeStamp;
    windValue* values = ParseStringToWind(inputString, updateTimeStamp);
    printf("windspeed: %lf, timestamp: %s\n", values[0].windspeed, values[0].timestamp);

    int i;
    for (i = 0; i < 97; ++i) {
        free(values[i].timestamp);
    }
    free(values);
    free(inputString);
    return (EXIT_SUCCESS);
}*/

/*cURL*/
/*static size_t cb(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(ptr == NULL)*/
/*        return 0;  *//* out of memory! */
/*
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}*/
/*memory GetDMIData(void)
{
    memory data;
    CURL *curl = curl_easy_init();
    if(curl) {*/
        /*https://www.dmi.dk/NinJo2DmiDk/ninjo2dmidk
         * opts from https://stackoverflow.com/questions/59454006/how-to-use-curl-in-c-and-parse-json-response
         * */
        /*curl_easy_setopt(curl, CURLOPT_URL, "https://www.dmi.dk/NinJo2DmiDk/ninjo2dmidk?cmd=llj&ids=2624886");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
         */
        /*https://curl.se/libcurl/c/CURLOPT_URL.html
         * https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html*/

        /* send all data to this function  */
        /*curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);*/
        /* we pass our 'chunk' struct to the callback function */
        /*memory chunk = {0};
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        curl_easy_perform(curl);
        printf("%s", chunk.response);
        data = chunk;
    }
    curl_easy_cleanup(curl);
    return data;
}*/