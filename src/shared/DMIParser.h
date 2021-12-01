#ifndef CO2_DMIPARSER_H

#define CO2_DMIPARSER_H

typedef struct windValue {
    char* timestamp;
    double windspeed;
} windValue;

windValue* ParseStringToWind(const char *input, char *lastUpdate);

#endif

