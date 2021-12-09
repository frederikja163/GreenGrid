#include <stdio.h>
#include <time.h>
#include <string.h>
#include "fileIO.h"
#include "calculateOptimalTime.h"
#include "timestamp.h"
#include "assertExtensions.h"

/* Algorithm to find the most optimal time to run based 
 * on array of windspeed data and the device's hours active
 */
char* find_optimal_time(int activeHours, int startSearch, int endSearch) {
    if (endSearch > 53) { /* 1 hour interval stops after 53 hours. */
        endSearch = 53;
    }

    int i;
    char *inputString;
    char *updateTimeStamp;
    inputString = read_file("bin/ninjo2dmidk.json");
    windValue *values = load_wind_data(inputString, &updateTimeStamp);
    free(inputString);
    
    double timeDiff = get_time_difference(updateTimeStamp);
    if (timeDiff >= 1) {
        free(updateTimeStamp);
        for (i = 0; i < 97; i++) {
            free(values[i].timestamp);
        }
        free(values);
        printf("Data is outdated, getting new data.\n");
        system("curl \"https://www.dmi.dk/NinJo2DmiDk/ninjo2dmidk?cmd=llj&ids=2624886\" -o bin/ninjo2dmidk.json");
        return find_optimal_time(activeHours, startSearch, endSearch);
    }
    startSearch += timeDiff;
    
    free(updateTimeStamp);

    char *optimalTime = find_lowest_co2(activeHours, values + startSearch, endSearch - startSearch);
    for (i = 0; i < 97; i++) {
        free(values[i].timestamp);
    }
    free(values);

    /* Remember to free the optimalTime value after use (To anyone using it) */
    return optimalTime;
}

void find_upper_and_lower_bounds(windValue *values, int dataSize, double *lowestCO2, double *highestCO2) {
    double currentCO2 = 0;
    *lowestCO2 = 99999;
    *highestCO2 = 0;
    int i;

    for (i = 0; i < dataSize; i++) {
        currentCO2 = calculate_co2(values[i].windspeed);
        if (currentCO2 > *highestCO2) {
            *highestCO2 = currentCO2;
        }
        else if (currentCO2 < *lowestCO2) {
            *lowestCO2 = currentCO2;
        }
    }
}

char* find_lowest_co2(int activeHours, windValue *values, int dataSize) {
    int i;
    double currentCO2 = 0;
    double lowestCO2 = 99999; 
    char *optimalTime = (char*) malloc(20*sizeof(char));
    assert_not_equal(optimalTime = malloc(20), NULL);
    
    for (i = 0; i < dataSize; i++) {
        currentCO2 += calculate_co2(values[i].windspeed);
        if (i >= activeHours-1) {
            currentCO2 -= calculate_co2(values[i-activeHours].windspeed);

            if (currentCO2 < lowestCO2) {
                lowestCO2 = currentCO2;
                strcpy(optimalTime, values[i-activeHours+1].timestamp);
            }
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