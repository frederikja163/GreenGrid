#include <stdio.h>
#include <stdlib.h>

#include "loadPseudoData.h"
#include "sum.h"

int main(void) {
    loadData("src/shared/input.txt", "src/shared/output.txt");

    return EXIT_SUCCESS;
}