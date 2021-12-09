#include "isDataOutdated.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool is_data_outdated(int maxTimeDiff, const char *receivingData) {
    time_t curTime = time(NULL);

    /* Converting receivingData into a timestamp via sscanf and the timeptr struct */
    struct tm timePtr;
    sscanf(receivingData, "%4d%02d%02d%02d%02d%02d",
           &timePtr.tm_year,
           &timePtr.tm_mon,
           &timePtr.tm_mday,
           &timePtr.tm_hour,
           &timePtr.tm_min,
           &timePtr.tm_sec);

    /* Correcting the default data from time.h */
    timePtr.tm_year -= 1900;
    timePtr.tm_mon -= 1;
    timePtr.tm_isdst = -1;

    time_t timeToStamp = mktime(&timePtr);

    double timeDiff = difftime(curTime, timeToStamp);

    if (timeDiff > maxTimeDiff) {
        /* Data is outdated */
        return true;
    } else {
        /* Data is not outdated */
        return false;
    }
}
