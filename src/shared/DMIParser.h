#ifndef CO2_DMIPARSER_H
#define CO2_DMIPARSER_H

typedef struct windValue {
    char* timestamp;
    double windspeed;
} windValue;

/* FIXME: Update file name and method name. */
windValue* ParseStringToWind(const char *input, char **lastUpdate);

#endif
