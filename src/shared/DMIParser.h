#ifndef DMIPARSER_H
#define DMIPARSER_H

typedef struct windValue {
    char* timestamp;
    double windspeed;
} windValue;

/* FIXME: Update file name and method name. */
windValue* load_wind_data(const char *input, char **lastUpdate);

#endif
