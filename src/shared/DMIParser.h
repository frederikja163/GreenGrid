#ifndef DMI_PARSER_H
#define DMI_PARSER_H

typedef struct windValue {
    char* timestamp;
    double windspeed;
} windValue;

windValue* load_wind_data(const char *input, char **lastUpdate);

#endif
