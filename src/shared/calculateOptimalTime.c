#include <stdio.h>
#include <time.h>
#include <string.h>
#include "fileIO.h"
#include "calculateOptimalTime.h"
#include "assertExtensions.h"

/* Algorithm to find the most optimal time to run based 
 * on array of windspeed data and the device's hours active
 */
char* find_optimal_time(int activeHours) {
    int i;
    char *inputString;
    char *updateTimeStamp;
    inputString = read_file("bin/ninjo2dmidk.json");
    windValue *values = load_wind_data(inputString, &updateTimeStamp);
    free(inputString);
    free(updateTimeStamp);

    char *optimalTime = find_lowest_co2(activeHours, values, DATA_SIZE);

    for (i = 0; i < 97; i++) {
        free(values[i].timestamp);
    }
    free(values);

    /* Remember to free the optimalTime value after use (To anyone using it) */
    return optimalTime;
}

char* find_lowest_co2(int activeHours, windValue *values, int data_size) {
    int i;
    double currentCO2 = 0;
    double lowestCO2; 
    char *optimalTime = (char*) malloc(20*sizeof(char));
    assert_not_equal(optimalTime = malloc(20), NULL);
    
    for (i = 0; i < data_size; i++) {
        currentCO2 += calculate_co2(values[i].windspeed);
        if (i >= activeHours) {
            currentCO2 -= calculate_co2(values[i-activeHours].windspeed);

            if (currentCO2 < lowestCO2) {
                lowestCO2 = currentCO2;
                strcpy(optimalTime, values[i-activeHours+1].timestamp);
            }
        }
        else if (i == activeHours - 1) {
            lowestCO2 = currentCO2;
            strcpy(optimalTime, values[0].timestamp);
        }
    }
    return optimalTime;
}

double calculate_co2(double windspeed) {
    double co2Level = 25;
    
    /* Cut-in and cut out speed of vestas windturbines */
    if (windspeed >= 3 && windspeed <= 25) {
        co2Level -= windspeed;
    }
    return co2Level;
}