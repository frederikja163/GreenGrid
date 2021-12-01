/* Calculating emissions Poggers */
#include <stdio.h>
#include <time.h>
#include "calculateOptimalTime.h"

    /* Function to load specific emission data in each timeslot */
void load_emission_data(emission_time *et, double emissions, int minsFromRequest) {
    et->emissions = emissions;
    et->hour = minsFromRequest;
}

    /* compare function, lowest emission value gets pushed first 
int compare_function (const void *ptr1, const void *ptr2) {
    const emission_time *elem1 = ptr1;
    const emission_time *elem2 = ptr2;

    return (elem1->emissions - elem2->emissions);
}
 */

    /* loads random data in the input array of structs */
void load_all_data(emission_time *data) {
    int i;
    int postiveOrNegative;
    double currentEmissions = 10000;
    srand(time(NULL));
    for(i = 0; i < DATA_SIZE; i++) {
            postiveOrNegative = rand()%2;
            if (postiveOrNegative) {
                currentEmissions = currentEmissions + rand()%100;
            } else {
                currentEmissions = currentEmissions + (rand()%100)*-1;
            }
            load_emission_data(&data[i], currentEmissions, i*10);
            printf ("Min from API request = %d, Emissions = %.2lf \n",data[i].hour, data[i].emissions);   
    }
}

    /* Algorithm to find the most optimal time to run based 
       on array of emission data and the device's hours active */
int find_optimal_time(int activeHours) {
    activeHours *= 6;
    int i, j;
    double currentEmissions = 0;
    double lowestEmissions = 999999999; 
    int optimalTime;
    emission_time data[DATA_SIZE];
    load_all_data(data);

    printf("\n--------------------------------\n");
    
    for(i = 0; i < DATA_SIZE-(activeHours+1); i++) { 
        currentEmissions = 0;
        for(j = 0; j < activeHours; j++) {
            currentEmissions += data[i+j].emissions;
        }
        if (currentEmissions < lowestEmissions) {
            lowestEmissions = currentEmissions;
            optimalTime = data[i].hour;
        }
    } 
    time_t curtime;

    time(&curtime);

    printf("Current time = %s", ctime(&curtime));
    
    return optimalTime;
}