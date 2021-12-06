#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "isDataOutdated.h"

bool is_data_outdated(int maxTimeDiff, const char * receivingData) {
    time_t curTime = time(NULL);
   /*  printf("Current timestamp = %ld\n", curTime); */

    /* We are now converting the receiving data(Charachter string) into a timestamp via 
    this function strptime and this timeptr struct. */
    struct tm timePtr;
    strptime(receivingData, "%Y%m%d%H%M%S", &timePtr);
    time_t timeToStamp = mktime(&timePtr);
    /* printf("Receiving timestamp = %ld\n", timetostamp); */

    double timeDiff = difftime(curTime, timeToStamp);
    /* printf("Difference between timestamps = %.0lf\n", timediff); */
    
    if (timeDiff > maxTimeDiff) {
        /* Data is outdated */
        return true;
    }
    else {
        /* Data is not outdated */
        return false;
    }
}
