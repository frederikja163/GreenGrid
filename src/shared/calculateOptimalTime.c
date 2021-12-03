#include "calculateOptimalTime.h"

    /* Algorithm to find the most optimal time to run based 
       on array of windspeed data and the device's hours active */
char * find_optimal_time(int activeHours) {
    int i;
    char *inputString;
    char *updateTimeStamp;
    inputString = read_file("bin/ninjo2dmidk.json");
    windValue *values = load_wind_data(inputString, &updateTimeStamp);
    free(inputString);
    free(updateTimeStamp);

    char *optimalTime = find_highest_windspeeds(activeHours, values, DATA_SIZE);

    for (i = 0; i < 97; ++i) {
        free(values[i].timestamp);
    }
    free(values);

    /* Remember to free the optimalTime value after use (To anyone using it) */
    return optimalTime;
}

char * find_highest_windspeeds(int activeHours, windValue *values, int data_size){
    int i, j;
    double currentWindspeed = 0;
    double highestWindspeed = 0; 
    char *optimalTime = (char*) calloc(20, sizeof(char));
    
    for(i = 0; i < data_size-(activeHours-1); i++) { 
        currentWindspeed = 0;
        for(j = 0; j < activeHours; j++) {
            /* Cut-in and cut out speed of vestas windturbines */
            if(values[i+j].windspeed >= 3 && values[i+j].windspeed <= 25) {
                currentWindspeed += values[i+j].windspeed;
            }
        }
        if (currentWindspeed > highestWindspeed) {
            highestWindspeed = currentWindspeed;
            strcpy(optimalTime, values[i].timestamp);
        }
    }
    return optimalTime;
}