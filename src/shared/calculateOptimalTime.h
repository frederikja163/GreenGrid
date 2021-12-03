#ifndef CALCULATEOPTIMALTIME_H

#define CALCULATEOPTIMALTIME_H
#define DATA_SIZE 53

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "dmiParser.h"
#include "fileIO.h"


char * find_highest_windspeeds(int activeHours, windValue *values, int);
char * find_optimal_time(int activeHours);

#endif