/* Calculating emissions Poggers */

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
