#ifndef DMI_PARSER_H
#define DMI_PARSER_H

#include <cJSON.h>

#define WINDVALUE_COUNT 48

typedef struct windValue {
    char* timestamp;
    double windspeed;
} windValue;
windValue* load_wind_data(const char *input, char **lastUpdate);
void get_last_update_from_json(cJSON *json, char **lastUpdate);
windValue* get_all_wind_values(cJSON *json);

#endif
