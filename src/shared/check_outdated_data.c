#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Run(int maxTimeDiff, char *aavild_data) {

    time_t cur_time; 
    //char * aavild_data = "20211122080000";
    struct tm timeptr;

    cur_time = time(NULL);
    printf("Current timestamp = %ld\n", cur_time);

    strptime(aavild_data, "%Y%m%d%H%M%S", &timeptr);
    time_t aav_time = mktime(&timeptr);
    printf("Aavild timestamp = %ld\n", aav_time);

    double timediff = difftime(cur_time, aav_time);
    printf("Difference between timestamps = %.0lf\n", timediff);
    
    if (timediff > maxTimeDiff) {
        //Fix new data
        return 1;
    }
    else {
        //no need to fix
        return 0;
    }  
}
