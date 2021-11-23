/* Calculating emissions Poggers */
#include <stdio.h>
#include <time.h>
#include "calculateOptimalTime.h"

    /* Function to load specific emission data in each timeslot */
void load_emission_data(emission_time *et, double emissions, int hour_from_request){
    et->emissions = emissions;
    et->hour = hour_from_request;
}

    /* compare function, lowest emission value gets pushed first 
int compare_function (const void *ptr1, const void *ptr2){
    const emission_time *elem1 = ptr1;
    const emission_time *elem2 = ptr2;

    return (elem1->emissions - elem2->emissions);
}
 */

    /* loads random data in the input array of structs */
void load_all_data(emission_time *data){
    int i;
    int postiveOrNegative;
    double currentEmissions = 10000;
    srand(time(NULL));
    for(i = 0; i < DATA_SIZE; i++) {
            postiveOrNegative = rand()%2;
            if (postiveOrNegative){
                currentEmissions = currentEmissions + rand()%500;
            } else {
                currentEmissions = currentEmissions + (rand()%500)*-1;
            }
            load_emission_data(&data[i], currentEmissions, i);
            printf ("Hours from API request = %d, Emissions = %.2lf \n",data[i].hour, data[i].emissions);   
    }
}

    /* Algorithm to find the most optimal time to run based 
       on array of emission data and the device's hours active */
int find_optimal_time(int active_hours){
    int i, j;
    double current_emissions = 0;
    double lowest_emissions = 999999999; 
    int optimal_time;
    emission_time data[DATA_SIZE];
    load_all_data(data);

    printf("\n--------------------------------\n");
    
    for(i = 0; i < DATA_SIZE-(active_hours+1); i++){ 
        current_emissions = 0;
        for(j = 0; j < active_hours; j++){
            current_emissions += data[i+j].emissions;
        }
        if (current_emissions < lowest_emissions){
            lowest_emissions = current_emissions;
            optimal_time = data[i].hour;
        }
    } 
    return optimal_time;
}