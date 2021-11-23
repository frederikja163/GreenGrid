#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "calculateOptimalTime.h"


int main(void) {
    emission_time list[DATA_SIZE];
    
    srand(time(NULL));
    printf("\nBefore sorting emission data\n");
    int i;
    int postiveOrNegative;
    double currentEmissions = 5000;
    for(i = 0; i < DATA_SIZE; i++) {
        postiveOrNegative = rand()%2;
        if (postiveOrNegative){
            currentEmissions = currentEmissions + rand()%500;
        } else {
            currentEmissions = currentEmissions + (rand()%500)*-1;
        }
        
        load_emission_data(&list[i], currentEmissions, i);
        printf ("Hours from API request = %d, Emissions = %.2lf \n",list[i].hour, list[i].emissions);   
    }

    printf("\nAfter sorting emission data\n");
    printf("--------------------------------------------------------\n");
    /* qsort(list, DATA_SIZE, sizeof(emission_time), compare_function); 
    for(i = 0; i < DATA_SIZE; i++) {
        printf ("Hours from API request = %d, Emissions = %.2lf \n",list[i].hour, list[i].emissions);
    } */
    printf ("%d", find_optimal_time(list, 3));

    return EXIT_SUCCESS;
}