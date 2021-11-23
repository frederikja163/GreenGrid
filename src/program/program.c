#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loadPseudoData.h"
#include "sum.h"

int main(void) {
    char *path_relative = "src/shared/";
    char *input = "src/shared/input.txt";
    char *output = "src/shared/output.txt";

    loadData(input, output);

    return EXIT_SUCCESS;
}