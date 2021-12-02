#include <stdio.h>
#include <stdlib.h>

#include "checkOutdatedData.h"

int main(void) {
    const char * receivingData = "20211122080000";
    check_outdated_data(88888, receivingData);
    return EXIT_SUCCESS;
}