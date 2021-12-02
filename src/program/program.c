#include <stdlib.h>
#include <stdio.h>
#include "calculateOptimalTime.h"

int main(int argc, char **argv) {
    char optimalTime[20];
    printf("Optimal time to run is: %s", find_optimal_time(3, optimalTime));
    return (EXIT_SUCCESS);
}