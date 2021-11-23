/* Calculating emissions Poggers */
#include <stdio.h>
#include "calculateOptimalTime.h"

    /* Function to load specific emission data in each timeslot */
void load_emission_data(emission_time *et, double emissions, int hour_from_request){
    et->emissions = emissions;
    et->hour = hour_from_request;
}

    /* compare function, lowest emission value gets pushed first */
int compare_function (const void *ptr1, const void *ptr2){
    const emission_time *elem1 = ptr1;
    const emission_time *elem2 = ptr2;

    return (elem1->emissions - elem2->emissions);
}

int find_optimal_time(emission_time *et, int active_hours){
    int i, j;
    double current_emissions = 0;
    double lowest_emissions = 999999999; 
    int optimal_time;
    printf("%d", et->emissions);
    for(i = 0; i < DATA_SIZE-(active_hours+1); i++){
        printf(" test[%d], ", i); 
        current_emissions = 0;
        for(j = 0; j < 3; j++){
            current_emissions += (et+i+j)->emissions;
            printf(" [%d]", (et+i+j)->hour);
        }
        if (current_emissions < lowest_emissions){
            lowest_emissions = current_emissions;
            optimal_time = (et+i)->hour;
            printf(", yay");
        }
    }
    return 123;
}