/*
 * Created by Aavild on 19/11/2021.
 */

#include "DMIParser.h"
#include "cJSON/cJSON.h"
#include "curl/curl.h"

typedef struct memory {
    char *response;
    size_t size;
} memory;

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

void main(void)
{
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
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, cb);
        /* we pass our 'chunk' struct to the callback function */
        memory chunk = {0};
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        printf("%s", chunk.response);

        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
}