#include "isDataOutdated.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool is_data_outdated(int maxTimeDiff, const char *receivingData) {
    time_t curTime = time(NULL);
    /*  printf("Current timestamp = %ld\n", curTime); */

    /* We are now converting the receiving data(Charachter string) into a timestamp via 
    this function strptime and this timeptr struct. */
    struct tm timePtr;
    sscanf(receivingData, "%4d%02d%02d%02d%02d%02d",
           &timePtr.tm_year,
           &timePtr.tm_mon,
           &timePtr.tm_mday,
           &timePtr.tm_hour,
           &timePtr.tm_min,
           &timePtr.tm_sec);

    timePtr.tm_year -= 1900;
    timePtr.tm_mon -= 1;
    timePtr.tm_isdst = -1;

    time_t timeToStamp = mktime(&timePtr);

    /* printf("Receiving timestamp = %ld\n", timetostamp); */

    double timeDiff = difftime(curTime, timeToStamp);
    /* printf("Difference between timestamps = %.0lf\n", timediff); */

    if (timeDiff > maxTimeDiff) {
        /* Data is outdated */
        return true;
    } else {
        /* Data is not outdated */
        return false;
    }
}
