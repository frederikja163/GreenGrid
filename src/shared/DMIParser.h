/*
 * Created by Aavild on 19/11/2021.
 */
#ifndef CO2_DMIPARSER_H

#define CO2_DMIPARSER_H

typedef struct windValue {
    int timestamp;
    double windspeed;
} windValue;

windValue* ParseStringToWind(const char *input, int *lastUpdate);

/*typedef struct memory {
    char *response;
    size_t size;
} memory;*/

/*static size_t cb(void *data, size_t size, size_t nmemb, void *userp);*/
/*memory GetDMIData(void);*/

#endif

