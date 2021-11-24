/*
 * Created by Aavild on 19/11/2021.
 */
#include <stdlib.h>
#include "DMIParser.h"
#include <cJSON.h>
#include <curl/curl.h>

typedef struct memory {
    char *response;
    size_t size;
} memory;
typedef struct windValue {
    int timestamp;
    double windspeed;
} windValue;

static size_t cb(void *data, size_t size, size_t nmemb, void *userp);
windValue* ParseStringToWind(const char* string);
memory GetDMIData(void);

static size_t cb(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(ptr == NULL)
        return 0;  /* out of memory! */

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

windValue* ParseStringToWind(const char* string)
{
    cJSON *json = cJSON_Parse(string);
    if (json == NULL)
    {
        const char *error = cJSON_GetErrorPtr();
        if (error != NULL)
        {
            printf("Error at: %s", error);
        }
        return 0;
    }

    cJSON *id = cJSON_GetObjectItem(json, "id");
    if (cJSON_IsString(id) && (id->valuestring != NULL))
    {
        printf("Checking id \"%s\"\n", id->valuestring);
    }
    cJSON_Delete(json);
    /*Test hertil i første omgang*/
    windValue *values = malloc(sizeof(windValue)*100);
    if(values == NULL)
        return 0;  /* out of memory! */
    int iterator = 0;
    cJSON *timeserie = cJSON_GetObjectItem(json, "timeserie");
    cJSON *hour;
    /*cJSON_ArrayForEach(hour, timeserie)
    {
        cJSON *time = cJSON_GetObjectItem(hour, "time");
        cJSON *windSpeed = cJSON_GetObjectItem(hour, "windSpeed");

        if (!cJSON_IsNumber(time) || !cJSON_IsNumber(windSpeed))
        {
            continue;
        }
        values[iterator].timestamp = time->valueint;
        values[iterator].windspeed = hour->valuedouble;
        iterator++;
    }*/

    cJSON_Delete(json);
    return values;
}

memory GetDMIData(void)
{
    memory data;
    CURL *curl = curl_easy_init();
    if(curl) {
        /*https://www.dmi.dk/NinJo2DmiDk/ninjo2dmidk
         * opts from https://stackoverflow.com/questions/59454006/how-to-use-curl-in-c-and-parse-json-response
         * */
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.dmi.dk/NinJo2DmiDk/ninjo2dmidk?cmd=llj&ids=2624886");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

        /*https://curl.se/libcurl/c/CURLOPT_URL.html
         * https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html*/

        /* send all data to this function  */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
        /* we pass our 'chunk' struct to the callback function */
        memory chunk = {0};
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        curl_easy_perform(curl);
        printf("%s", chunk.response);
        data = chunk;
    }
    curl_easy_cleanup(curl);
    return data;
}