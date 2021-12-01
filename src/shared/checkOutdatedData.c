#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check_outdated_data(int maxTimeDiff, const char *receivingData) {
    time_t curTime = time(NULL);
   /*  printf("Current timestamp = %ld\n", curTime); */

    struct tm timeptr;
    /* We are now converting the recieving data(Charachter string) into a timestamp via 
    this function strptime and this timeptr struct. */
    strptime(receivingData, "%Y%m%d%H%M%S", &timeptr);
    time_t timeToStamp = mktime(&timeptr);
    /* printf("Receving timestamp = %ld\n", timetostamp); */

    double timediff = difftime(curTime, timeToStamp);
    /* printf("Difference between timestamps = %.0lf\n", timediff); */
    
    if (timediff > maxTimeDiff) {
        /* Fix new data */
        return 1;
    }
    else {
        /* no need to fix */
        return 0;
    }  
}
