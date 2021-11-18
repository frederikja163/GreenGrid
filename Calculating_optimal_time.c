/* Calculating emissions Poggers */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

    /* Looking a week ahead in intervals consisting of hours */
#define DATA_SIZE 10

    /* data containing the emission expected at a certain time from requested data */
struct emission_time
{
    double emissions;
    int hour;
};
typedef struct emission_time emission_time;

int compare_function (const void *ptr1, const void *ptr2);
void load_emission_data(emission_time *et, double emissions, int hour);

int main(void){
    emission_time list[DATA_SIZE];
    
    srand ( time(NULL) );
    printf("\nBefore sorting emission data\n");
    int i;
    for(i = 0; i < DATA_SIZE; i++){
        load_emission_data(&list[i], rand()%10000, i);
        printf ("Hours from API request = %d, Emissions = %.2lf \n",list[i].hour, list[i].emissions);   
    }

    printf("\nAfter sorting emission data\n");
    printf("--------------------------------------------------------\n");
    qsort(list, DATA_SIZE, sizeof(emission_time), compare_function);
    for(int i = 0; i < DATA_SIZE; i++){
        printf ("Hours from API request = %d, Emissions = %.2lf \n",list[i].hour, list[i].emissions);
    }
}

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
