#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "calculateOptimalTime.h"


int main(void) {
    emission_time list[DATA_SIZE];
    
    srand(time(NULL));
    printf("\nBefore sorting emission data\n");
    int i;
    for(i = 0; i < DATA_SIZE; i++) {
        load_emission_data(&list[i], rand()%10000, i);
        printf ("Hours from API request = %d, Emissions = %.2lf \n",list[i].hour, list[i].emissions);   
    }

    printf("\nAfter sorting emission data\n");
    printf("--------------------------------------------------------\n");
    qsort(list, DATA_SIZE, sizeof(emission_time), compare_function);
    for(i = 0; i < DATA_SIZE; i++) {
        printf ("Hours from API request = %d, Emissions = %.2lf \n",list[i].hour, list[i].emissions);
    }

    return EXIT_SUCCESS;
}