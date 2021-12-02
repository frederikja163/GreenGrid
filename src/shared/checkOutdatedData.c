#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check_outdated_data(int maxTimeDiff, const char * receivingData) {
    time_t curTime = time(NULL);
   /*  printf("Current timestamp = %ld\n", curTime); */

    /* We are now converting the recieving data(Charachter string) into a timestamp via 
    this function strptime and this timeptr struct. */
    struct tm timePtr;
    strptime(receivingData, "%Y%m%d%H%M%S", &timePtr);
    time_t timeToStamp = mktime(&timePtr);
    /* printf("Receving timestamp = %ld\n", timetostamp); */

    double timeDiff = difftime(curTime, timeToStamp);
    /* printf("Difference between timestamps = %.0lf\n", timediff); */
    
    if (timeDiff > maxTimeDiff) {
        /* Fix new data */
        return 1;
    }
    else {
        /* no need to fix */
        return 0;
    }  
}
