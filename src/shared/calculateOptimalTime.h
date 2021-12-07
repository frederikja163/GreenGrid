#ifndef CALCULATEOPTIMALTIME_H

#define CALCULATEOPTIMALTIME_H
#define DATA_SIZE 53

#include "dmiParser.h"


char* find_lowest_co2(int activeHours, windValue *values, int);
void find_upper_and_lower_bounds(windValue *values, int dataSize, double *lowestCO2, double *highestCO2);
char* find_optimal_time(int activeHours);
double calculate_co2(double);

#endif